#include <pspkernel.h>
#include <pspctrl.h>
#include <pspreg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <psprtc.h>
#include "kubridge.h"
#include "kirk_engine.h"
#include "zlib.h"
#include "../ppatch_config.h"
#include "systemctrl.h"
#include "printf_chs.h"///+

typedef struct header_keys {
    u8 AES[16];
    u8 CMAC[16];
} header_keys;

/* VSH module can write F0 */
PSP_MODULE_INFO("Installer", 0x800, 1, 2);
PSP_HEAP_SIZE_KB(1*1024);

#define CTRL_DELAY   100000
#define CTRL_DEADZONE_DELAY 500000

#define printf CHS_ScreenPrintf///|#define printf pspDebugScreenPrintf

static u8 buf[64*1024] __attribute__((aligned(64)));
static u8 buf1[64*1024] __attribute__((aligned(64)));
static u8 buf2[64*1024] __attribute__((aligned(64)));

static u8 vshmain_pspheader[0x150] __attribute__((aligned(64)));
static u8 vshmain_kirkheader[0x110] __attribute__((aligned(64)));

static u8 in_buffer[512*1024] __attribute__((aligned(64)));
static u8 out_buffer[512*1024] __attribute__((aligned(64)));

static u8 kirk_raw[512*1024] __attribute__((aligned(64)));
static u8 kirk_enc[512*1024] __attribute__((aligned(64)));
static u8 elf[512*1024] __attribute__((aligned(64)));

extern int get_kirk_header(void *buf);
extern int kuKernelGetModel(void);

int load_start_module(char *path)
{
	int ret;
	SceUID modid;
	int status;

	modid = kuKernelLoadModule(path, 0, NULL);

	status = 0;
	ret = sceKernelStartModule(modid, strlen(path) + 1, path, &status, NULL);

	return ret;
}

void init_flash(void)
{
	int ret;

retry:
	sceKernelDelayThread(200000);
	ret = sceIoUnassign("flash0:");

	if(ret < 0) {
		goto retry;
	}

	ret = sceIoAssign("flash0:", "lflash0:0,0", "flashfat0:", 0, NULL, 0);

	if(ret < 0) {
		goto retry;
	}

	ret = sceIoUnassign("flash1:");

	if(ret < 0) {
		goto retry;
	}

	ret = sceIoAssign("flash1:", "lflash0:0,1", "flashfat1:", 0, NULL, 0);

	if(ret < 0) {
		goto retry;
	}
}

int compare_file(const char *src, const char *dst)
{
	SceUID fd = -1, fdd = -1;
	int ret, ret2;
	SceIoStat srcstat, dststat;

	ret = sceIoGetstat(src, &srcstat);
	
	if (ret != 0) {
		goto not_equal;
	}

	ret = sceIoGetstat(dst, &dststat);
	
	if (ret != 0) {
		goto not_equal;
	}

	if (dststat.st_size != srcstat.st_size) {
		goto not_equal;
	}

	ret = sceIoOpen(src, PSP_O_RDONLY, 0777);

	if (ret < 0) {
		goto not_equal;
	}

	fd = ret;

	ret = sceIoOpen(dst, PSP_O_RDONLY, 0777);

	if (ret < 0) {
		goto not_equal;
	}

	fdd = ret;
	ret = sizeof(buf1);
	ret = sceIoRead(fd, buf1, ret);

	while (ret > 0) {
		ret2 = sceIoRead(fdd, buf2, ret);

		if (ret2 != ret) {
			goto not_equal;
		}

		if (memcmp(buf1, buf2, ret)) {
			goto not_equal;
		}

		ret = sceIoRead(fd, buf1, ret);
	}

	if (ret < 0) {
		goto not_equal;
	}

	sceIoClose(fd);
	sceIoClose(fdd);

	return 0;

not_equal:
	if (fd >= 0)
		sceIoClose(fd);

	if (fdd >= 0)
		sceIoClose(fdd);

	return 1;
}

int copy_file(const char *src, const char *dst)
{
	SceUID fd = -1, fdw = -1;
	int ret;

	ret = sceIoOpen(src, PSP_O_RDONLY, 0777);

	if (ret < 0) {
		goto error;
	}

	fd = ret;

	ret = sceIoOpen(dst, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

	if (ret < 0) {
		goto error;
	}

	fdw = ret;
	ret = sizeof(buf);
	ret = sceIoRead(fd, buf, ret);

	while (ret > 0) {
		ret = sceIoWrite(fdw, buf, ret);

		if (ret < 0) {
			goto error;
		}

		ret = sceIoRead(fd, buf, ret);
	}

	if (ret < 0) {
		goto error;
	}

	sceIoClose(fd);
	sceIoClose(fdw);

	return 0;

error:
	sceIoClose(fd);
	sceIoClose(fdw);

	return ret;
}

int write_file(const char *path, unsigned char *buf, int size)
{
	SceUID fd;
	int ret;

	fd = sceIoOpen(path, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

	if (fd < 0) {
		goto error;
	}

	ret = sceIoWrite(fd, buf, size);

	if (ret < 0) {
		goto error;
	}

	sceIoClose(fd);

	return 0;
error:
	if (fd >= 0)
		sceIoClose(fd);

	return -1;
}

int load_binary(const char *path, void *buf, int offset, int size)
{
	SceUID fd;
	int ret;

	fd = sceIoOpen(path, PSP_O_RDONLY, 0777);

	if(fd < 0) {
		return fd;
	}

	sceIoLseek32(fd, offset, PSP_SEEK_SET);
	ret = sceIoRead(fd, buf, size);

	if(ret != size) {
		sceIoClose(fd);

		return -1;
	}

	sceIoClose(fd);
	
	return ret;
}

int get_vshmain_prx_header(void)
{
	int ret;

	ret = load_binary(VSHORIG, vshmain_pspheader, 0, sizeof(vshmain_pspheader));

	if(ret < 0)
		return ret;

	return 0;
}

int is_file_exist(const char *path)
{
	SceIoStat stat;
	int ret;

	ret = sceIoGetstat(path, &stat);

	return ret == 0 ? 1 : 0;
}

int is_already_installed(void)
{
	if(!is_file_exist(VSHORIG)) {
		return 0;
	}

	if(0 == compare_file(VSHMAIN, VSHORIG)) {
		return 0;
	}

	return 1;
}

static u32 g_last_btn = 0;
static u32 g_last_tick = 0;
static u32 g_deadzone_tick = 0;

u32 ctrl_read(void)
{
	SceCtrlData ctl;

	sceCtrlReadBufferPositive(&ctl, 1);

	if (ctl.Buttons == g_last_btn) {
		if (ctl.TimeStamp - g_deadzone_tick < CTRL_DEADZONE_DELAY) {
			return 0;
		}

		if (ctl.TimeStamp - g_last_tick < CTRL_DELAY) {
			return 0;
		}

		g_last_tick = ctl.TimeStamp;

		return g_last_btn;
	}

	g_last_btn = ctl.Buttons;
	g_deadzone_tick = g_last_tick = ctl.TimeStamp;

	return g_last_btn;
}

int confirm_testrun(void)
{
	u32 key;
	int ret = 0;

	printf("\241\326\241\371\241\274 vshmain\241\355\242\251\242\242\241\364\241\255\241\341\241\244[\241\330\241\322\241\351\241\315]\n\241\334\241\306\241\337\241\246\241\243\241\326\241\374\241\303\241\346\242\246\241\245\242\251\241\253\241\250\241\304\241\311\241\321\241\241\n");///|printf("Are you going to have a test run on fake vshmain? [STRONGLY RECOMMENDED]\nIf it failed you should stop installing and report it back.\n");
	printf("X - \241\340, O - \241\301\n");///|printf("X - Yes, O - No\n");

	while ( 1 ) {
		key = ctrl_read();

		if(key & PSP_CTRL_CIRCLE) {
			ret = 0;
			break;
		} else if(key & PSP_CTRL_CROSS) {
			ret = 1;
			break;
		}
	}

	return ret;
}

int confirm_install(void)
{
	u32 key;
	int ret = 0;

	printf("\241\326\241\371\241\245\242\251\241\254\241\273\241\323\241\244\n");///|printf("Are you going to install the patch?\n");
	printf("X - \241\340, O - \241\301\n");///|printf("X - Yes, O - No\n");

	while ( 1 ) {
		key = ctrl_read();

		if(key & PSP_CTRL_CIRCLE) {
			ret = 0;
			break;
		} else if(key & PSP_CTRL_CROSS) {
			ret = 1;
			break;
		}
	}

	return ret;
}

int confirm_uninstall(void)
{
	u32 key;
	int ret = 0;

	printf("\241\326\241\371\241\363\242\243\241\254\241\273\241\323\241\244\n");///|printf("Are you going to uninstall the patch?\n");
	printf("X - \241\340, O - \241\301\n");///|printf("X - Yes, O - No\n");

	while ( 1 ) {
		key = ctrl_read();

		if(key & PSP_CTRL_CIRCLE) {
			ret = 0;
			break;
		} else if(key & PSP_CTRL_CROSS) {
			ret = 1;
			break;
		}
	}

	return ret;
}

int load_elf(const char *path)
{
	SceIoStat stat;
	int ret;

	ret = sceIoGetstat(path, &stat);

	if(ret < 0) {
		return ret;
	}

	ret = load_binary(path, elf, 0, stat.st_size);

	return ret;
}

int gzip_compress(u8 *dst, const u8 *src, int size)
{
	int ret;
	z_stream strm;
	u8 *elf_compress;
	const int compress_max_size = 512*1024;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

	elf_compress = malloc(compress_max_size);

	if(elf_compress == NULL) {
		return -1;
	}

	ret = deflateInit2(&strm, 9, Z_DEFLATED, 15+16, 8, Z_DEFAULT_STRATEGY);

	if(ret != Z_OK) {
		printf("%s: \241\367\241\343\241\266\241\360\n", __func__);///|printf("%s: compress error\n", __func__);
		free(elf_compress);
		
		return -2;
	}

	strm.avail_in = size;
	strm.next_in = (void*)src;
	strm.avail_out = compress_max_size;
	strm.next_out = elf_compress;

	ret = deflate(&strm, Z_FINISH);

	if(ret == Z_STREAM_ERROR) {
		deflateEnd(&strm);
		printf("%s: \241\367\241\343\241\266\241\360\n", __func__);///|printf("%s: compress error\n", __func__);
		free(elf_compress);

		return -3;
	}

	memcpy(dst, elf_compress, strm.total_out);
	deflateEnd(&strm);
	free(elf_compress);

	return 0;
}

int get_kirk_size(u8 *key_hdr)
{
	int krawSize = *(u32*)(key_hdr+0x70);

	if(krawSize % 0x10) {
		krawSize += 0x10 - (krawSize % 0x10); // 16 bytes aligned
	}

	krawSize += 0x110;

	return krawSize;
}

int get_elf_size(u8 *kirk_header)
{
//	return *(int*)(kirk_header+0xB8);
	return 391096;
}

int forge_vshmain(u8 *psp_header, u8 *kirk_header)
{
	header_keys keys;
	u8 rawkheaderBk[0x90];
	int ret;

	memset(in_buffer, 0, sizeof(in_buffer));
	memset(out_buffer, 0, sizeof(out_buffer));
	memset(kirk_raw, 0, sizeof(kirk_raw));
	memset(kirk_enc, 0, sizeof(kirk_enc));
	memset(elf, 0, sizeof(elf));

	kirk_init();

	int elfSize = load_elf(PRXPATH);

	if(elfSize < 0) {
		printf("\241\357\241\275\241\313\242\243 %s\n", PRXPATH);///|printf("cannot load %s\n", PRXPATH);
		
		return elfSize;
	}

	int krawSize = get_kirk_size(kirk_header);

	if(elfSize > krawSize - 0x150) {
		printf("PRX \241\345\241\267\241\242\n");///|printf("PRX is too big!\n");

		return -1;
	}

	elfSize = get_elf_size(psp_header);
	ret = gzip_compress(elf, elf, elfSize);

	if(ret < 0) {
		printf("\241\357\241\275\241\367\241\343elf\n");///|printf("Could not compress elf\n");
		
		return ret;
	}

	memcpy(kirk_raw, kirk_header, 0x110);
	memcpy(rawkheaderBk, kirk_raw, sizeof(rawkheaderBk));

	kirk_decrypt_keys((u8*)&keys, kirk_raw);
	memcpy(kirk_raw, &keys, sizeof(header_keys));
	memcpy(kirk_raw+0x110, elf, elfSize);

	if(kirk_CMD0(kirk_enc, kirk_raw, sizeof(kirk_enc), 0) != 0) {
		printf("\241\357\241\275\241\313\241\324elf\n");///|printf("Could not encrypt elf\n");

		return -2;
	}

	memcpy(kirk_enc, rawkheaderBk, sizeof(rawkheaderBk));

	ret = kirk_forge(kirk_enc, sizeof(kirk_enc));

	if(ret != 0) {
		printf("\241\357\241\275\241\355\242\245cmac\241\320 0x%08X\n", ret);///|printf("Could not forge cmac block 0x%08X\n", ret);

		return -3;
	}

	memcpy(out_buffer, psp_header, 0x150);
	memcpy(out_buffer+0x150, kirk_enc+0x110, krawSize-0x110);

	ret = write_file(VSHTEMP, out_buffer, (krawSize-0x110)+0x150);

	if(ret != 0) {
		printf("\241\357\241\275\241\362\241\335\241\356\241\316 0x%08X\n", ret);///|printf("Could not write file 0x%08X\n", ret);
		
		return ret;
	}

	return 0;
}

int get_vshmain_kirk_header(void)
{
	int ret;
	SceUID modid;

	ret = load_start_module(MODPATH);

	if(ret < 0)
		return ret;

	sceKernelDelayThread(100000);

	modid = kuKernelLoadModule(VSHMAIN, 0, NULL);

	if(modid < 0) {
		return modid;
	}

	ret = get_kirk_header(vshmain_kirkheader);

	if(ret < 0) {
		return ret;
	}

	sceKernelUnloadModule(modid);

	return 0;
}

int is_module_loadable(const char *path)
{
	SceUID modid;
	int result = 0;

	modid = kuKernelLoadModule(path, 0, NULL);

	if (modid >= 0) {
		sceKernelUnloadModule(modid);
		result = 1;
	} else {
		printf("\241\325\241\320\241\313\242\243\241\341\241\370 -> 0x%08X\n", modid);///|printf("Module loading test -> 0x%08X\n", modid);
	}

	return result;
}

int final_check(void)
{
	int ret;

	ret = is_module_loadable(VSHTEMP);

	if(!ret) {
		ret = -1;
		goto exit;
	}

	ret = is_file_exist(VSHORIG);

	if(!ret) {
		ret = -2;
		goto exit;
	}

	ret = compare_file(VSHORIG, VSHTEMP);

	if(ret == 0) {
		ret = -3;
		goto exit;
	}

	ret = 0;
exit:
	return ret;
}

char ownisgraph (u8 c)
{
    if ( c >= 0x21 && c <= 0x7e )
        return 1;

    return 0;
}

void hexdump(void *addr, int size)
{
	int i;
	u8 *p = (u8*)addr;

	if (addr == NULL) {
		printf("hexdump: <NULL>\n");

		return;
	}

	if (size == 0) {
		printf("hexdump: size 0\n");
		
		return;
	}

	printf("Address:   ");
	i=0; for(;i<16; ++i) {
		if (i == 8)
			printf("- ");
		
		printf("%02X ", i);
	}

	i=0; for(;i<16; ++i) {
		printf("%1X", i);
	}

	printf("\n-----------------------------------------------------------------------------\n");

	i=0;
	printf("0x%08X ", i);
	
	for(; i<size; ++i) {
		if (i != 0 && i % 16 == 0) {
			int j;

			for(j=16; j>0; --j) {
				if(ownisgraph(p[i-j])) {
					printf("%c", p[i-j]);
				} else {
					printf(".");
				}
			}
			printf("\n0x%08X ", i);
		}

		if (i != 0 && i % 8 == 0 && i % 16 != 0) {
			printf("- ");
		}

		printf("%02X ", p[i]);
	}

	int rest = (16-(i%16));

	rest = rest == 16 ? 0 : rest;
	int j; for(j=0; j<rest; j++) {
		if (j+(i%16) == 8)
			printf("  ");
		printf("   ");
	}

	rest = i % 16;
	rest = rest == 0 ? 16 : rest;

	for(j=rest; j>0; --j) {
		if(ownisgraph(p[i-j])) {
			printf("%c", p[i-j]);
		} else {
			printf(".");
		}
	}

	printf("\n");
}

void uninstall(void)
{
	int ret;

	do {
		ret = sceIoRemove(VSHMAIN);

		if(ret != 0) {
			printf("\241\336\241\262 %s\241\337\241\246\n", VSHMAIN);///|printf("Delete %s failed\n", VSHMAIN);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);

	do {
		ret = copy_file(VSHORIG, VSHMAIN);

		if(ret != 0) {
			printf("\241\302\242\247 %s\241\270 %s\241\337\241\2460x%08X\n", VSHORIG, VSHMAIN, ret);///|printf("Copy %s to %s failed 0x%08X\n", VSHORIG, VSHMAIN, ret);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);

	do {
		ret = sceIoRemove(VSHORIG);

		if(ret != 0) {
			printf("\241\336\241\262 %s\241\337\241\246\n", VSHTEMP);///|printf("Delete %s failed\n", VSHTEMP);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);
}

void install(void)
{
	int ret;

	do {
		ret = sceIoRemove(VSHMAIN);

		if(ret != 0) {
			printf("\241\336\241\262 %s\241\337\241\246\n", VSHMAIN);///|printf("Delete %s failed\n", VSHMAIN);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);

	do {
		ret = copy_file(VSHTEMP, VSHMAIN);

		if(ret != 0) {
			printf("\241\302\242\247 %s\241\270 %s\241\337\241\246 0x%08X\n", VSHTEMP, VSHMAIN, ret);///|printf("Copy %s to %s failed 0x%08X\n", VSHTEMP, VSHMAIN, ret);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);

	do {
		ret = sceIoRemove(VSHTEMP);

		if(ret != 0) {
			printf("\241\336\241\262 %s\241\337\241\246\n", VSHTEMP);///|printf("Delete %s failed\n", VSHTEMP);
			sceKernelDelayThread(1000000L);
		}
	} while(ret != 0);
}

int main()
{
	int fw_version, ret;

	CHS_ScreenInit();///|pspDebugScreenInit();
	printf("6.20 PRO Permanent Patch By Team PRO\n");
	fw_version = sceKernelDevkitVersion();

	if(fw_version != 0x06020010 || sctrlHENGetMinorVersion() == 0x8002013A) {
		printf("\241\263\241\260\241\366\241\365\241\3716.20 PRO\n");///|printf("This program requires 6.20 PRO\n");
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

	init_flash();
	printf("\241\347\241\307\242\242\241\364\241\303\241\374\241\375\241\260\241\366\241\327\241\317\241\342\241\344\241\376\241\271\241\300\241\361\241\241\n\n");///|printf("BY RUNNING THIS APPLICATION YOU ACCEPT ALL THE RISK INVOLVED.\n\n");
	
	if(is_already_installed() != 0) {
		if(confirm_uninstall()) {
			uninstall();
			printf("\241\363\242\243\241\353\241\257\n");///|printf("Uninstall completed\n");
			sceKernelDelayThread(2 * 1000000L);
		}

		goto exit;
	}

	if (!confirm_install()) {
		goto exit;
	}

	// backup vshmain
	ret = copy_file(VSHMAIN, "ms0:/vshorig.prx");

	if(ret < 0) {
		ret = copy_file(VSHMAIN, "ef0:/vshorig.prx");

		if(ret < 0) {
			printf("\241\251\241\277\241\337\241\246 0x%08X\n", ret);///|printf("Backup failed 0x%08X\n", ret);
			sceKernelDelayThread(2 * 1000000L);
			goto exit;
		} else {
			printf("\242\241 vshmain.prx\241\373\241\252\241\247\241\265\241\354 ef0:/vshorig.prx\n");///|printf("The original vshmain.prx has been saved as ef0:/vshorig.prx\n");
		}
	} else {
		printf("\242\241 vshmain.prx\241\373\241\252\241\247\241\265\241\354 ms0:/vshorig.prx\n");///|printf("The original vshmain.prx has been saved as ms0:/vshorig.prx\n");
	}

	printf("\241\331\241\247\241\265\242\244\241\372\241\305\241\245\241\333\241\271\241\272\241\276\n");///|printf("Please keep it in a safe place\n");

	ret = copy_file(VSHMAIN, VSHORIG);

	if(ret < 0) {
		printf("\241\302\242\247 %s\241\270 %s\241\337\241\246 0x%08X\n", VSHMAIN, VSHORIG, ret);///|printf("Copy %s to %s failed 0x%08X\n", VSHMAIN, VSHORIG, ret);
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

	ret = get_vshmain_prx_header();

	if(ret < 0) {
		printf("\241\264\242\241 vshmain\241\312\241\332 PSP\241\350\241\337\241\246 %08X\n", ret);///|printf("Get psp header from original vshmain failed %08X\n", ret);
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

	ret = get_vshmain_kirk_header();

	if(ret < 0) {
		printf("\241\264\242\241 vshmain\241\312\241\332kirk\241\350\241\337\241\246 %08X\n", ret);///|printf("Get kirk header from original vshmain failed %08X\n", ret);
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

//	hexdump(vshmain_kirkheader, sizeof(vshmain_kirkheader));
	ret = forge_vshmain(vshmain_pspheader, vshmain_kirkheader);

	if(ret < 0) {
		printf("\241\355\242\251 vshmain\241\337\241\246 %08X\n", ret);///|printf("forge fake vshmain failed %08X\n", ret);
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

	if(confirm_testrun()) {
		ret = load_start_module(VSHTEMP);

		while ( 1 ) {
			sceKernelSleepThread();
		}
	}

	ret = final_check();

	if(ret < 0) {
		printf("\242\252\241\310\241\314\241\256\241\337\241\246 %08X\n", ret);///|printf("final check failed %08X\n", ret);
		sceKernelDelayThread(2 * 1000000L);
		goto exit;
	}

	install();
	printf("\241\245\242\251\241\353\241\257\n");///|printf("Installed completed\n");

exit:
	printf("\241\352\241\261\242\250...\n");///|printf("Exiting...\n");
	sceKernelDelayThread(1000000);
	sceKernelExitGame();
	
	return 0;
}
