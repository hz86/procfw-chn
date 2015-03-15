/********************************
	ipl Flasher 


*********************************/
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <kubridge.h>

#include "pspipl_update.h"
#include "../CIPL/ipl_block_large.h"
#include "../CIPL/ipl_block_01g.h"
#include "printf_chs.h"///+

PSP_MODULE_INFO("IPLFlasher", 0x0800, 1, 0); 
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_VSH);

#if _PSP_FW_VERSION == 639
#define DEVKIT_VER	0x06030910
#define VERSION_STR	"6.39"
#elif _PSP_FW_VERSION == 660
#define DEVKIT_VER	0x06060010
#define VERSION_STR	"6.60"
#elif _PSP_FW_VERSION == 661
#define DEVKIT_VER	0x06060110
#define VERSION_STR	"6.61"
#endif

#define printf CHS_ScreenPrintf///|#define printf pspDebugScreenPrintf
#define WHITE 0xFFFFF1
#define GREEN 0x0000FF00

u32 sceSysregGetTachyonVersion(void);		// 0xE2A5D1EE

char msg[256];
int model;
static u8 orig_ipl[0x24000] __attribute__((aligned(64)));

int ReadFile(char *file, int seek, void *buf, int size)
{
	SceUID fd = sceIoOpen(file, PSP_O_RDONLY, 0);
	if (fd < 0)
		return fd;

	if (seek > 0)
	{
		if (sceIoLseek(fd, seek, PSP_SEEK_SET) != seek)
		{
			sceIoClose(fd);
			return -1;
		}
	}

	int read = sceIoRead(fd, buf, size);
	
	sceIoClose(fd);
	return read;
}


////////////////////////////////////////
void ErrorExit(int milisecs, char *fmt, ...) 
{
	va_list list;
	va_start(list, fmt);
	vsprintf(msg, fmt, list);
	va_end(list);
	printf(msg);
	sceKernelDelayThread(milisecs*1000);
	sceKernelExitGame(); 
}
////////////////////////////////////////
u8 nand_buff[0x40000];
void flash_ipl(int size)
{

	printf("Flashing IPL...");

//	if(ReadFile("ipl_block.bin", 0 , ipl_block_large , 0x4000) < 0)
//		ErrorExit(5000,"Failed to load custom ipl!\n");

	if(pspIplUpdateClearIpl() < 0)
		ErrorExit(5000,"\241\311\241\265\241\301\241\256 ipl\241\242\n");///|ErrorExit(5000,"Failed to clear ipl!\n");

	if (pspIplUpdateSetIpl( ipl_block_large , size + 0x4000 ) < 0)
		ErrorExit(5000,"\241\311\241\265\241\315\241\303 ipl\241\242\n");///|ErrorExit(5000,"Failed to write ipl!\n");

	printf("\241\306\241\253\241\241\n");///|printf("Done.\n");

}

int is_ta88v3(void)
{
	u32 model, tachyon;

	tachyon = sceSysregGetTachyonVersion();
	model = kuKernelGetModel();

	if(model == 1 && tachyon == 0x00600000) {
		return 1;
	}

	return 0;
}

int main() 
{
	int devkit, size;
	SceUID kpspident;
	SceUID mod;

	(void)size_ipl_block_large;

	CHS_ScreenInit();///|pspDebugScreenInit();
	CHS_ScreenSetTextColor(WHITE);///|pspDebugScreenSetTextColor(WHITE);
	devkit = sceKernelDevkitVersion();

	if(devkit != DEVKIT_VER ) {
		ErrorExit(5000,"FW\241\260\241\312\241\242\n");///|ErrorExit(5000,"FW ERROR!\n");
	}

	kpspident = pspSdkLoadStartModule("kpspident.prx", PSP_MEMORY_PARTITION_KERNEL);

	if (kpspident < 0) {
		ErrorExit(5000, "kpspident.prx \241\272\241\323\241\304\241\250\n");///|ErrorExit(5000, "kpspident.prx loaded failed\n");
	}

	model = kuKernelGetModel();

	if(!(model == 0 || model == 1) || is_ta88v3()) {
		ErrorExit(5000,"\241\257\241\246\241\327\241\254\241\317\241\251\241\324\241\255\241\257\241\276\241\305\241\241\n");///|ErrorExit(5000,"This installer does not support this model.\n");
	}

	if( model == 0 ) {
		memcpy( ipl_block_large , ipl_block_01g, 0x4000);
	}

	//load module
	mod = sceKernelLoadModule("ipl_update.prx", 0, NULL);

	if (mod < 0) {
		ErrorExit(5000,"\241\311\241\265\241\272\241\323ipl_update.prx\241\242\n");///|ErrorExit(5000,"Could not load ipl_update.prx!\n");
	}

	mod = sceKernelStartModule(mod, 0, NULL, NULL, NULL);

	if (mod < 0) {
		ErrorExit(5000,"\241\311\241\265\241\300\241\264\241\276\241\274\241\242\n");///|ErrorExit(5000,"Could not start module!\n");
	}

	size = pspIplUpdateGetIpl(orig_ipl);

	if(size < 0) {
		ErrorExit(5000,"\241\311\241\265\241\271\241\262 ipl\241\242\n");///|ErrorExit(5000,"Failed to get ipl!\n");
	}

	printf("\n\241\330\241\263\241\320ipl Flasher \241\307"VERSION_STR"\241\241\n\n\n");///|printf("\nCustom ipl Flasher for "VERSION_STR".\n\n\n");

	int ipl_type = 0;

	if( size == 0x24000 ) {
		printf("\241\246\241\327\241\330\241\263\241\320ipl\n");///|printf("Custom ipl is installed\n");
		size -= 0x4000;
		memmove( ipl_block_large + 0x4000 , orig_ipl + 0x4000 , size);
		ipl_type = 1;
	} else if( size == 0x20000 ) {
		printf("\241\322ipl \n");///|printf("Raw ipl \n");
		memmove( ipl_block_large + 0x4000, orig_ipl, size);
	} else {
		printf("ipl \241\261\241\314;%08X\n", size);///|printf("ipl size;%08X\n", size);
		ErrorExit(5000,"\241\310\241\325 ipl\241\242\n");///|ErrorExit(5000,"Unknown ipl!\n");
	}

	printf(" \241\247\241\245\241\273");///|printf(" Press X to ");

	if( ipl_type ) {
		printf("\241\326\241\316");///|printf("Re");
	}

	printf("\241\246\241\327CIPL\n");///|printf("install CIPL\n");

	if( ipl_type ) {
		printf(" \241\247\241\243\241\273\241\252\241\256CIPL\241\266\241\270\241\322\241\322IPL\n");///|printf(" Press O to Erase CIPL and Restore Raw IPL\n");
	}

	printf(" \241\247\241\244\241\273\241\302\241\313\n\n");///|printf(" Press R to cancel\n\n");
    
	while (1) {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);

		if (pad.Buttons & PSP_CTRL_CROSS) {
			flash_ipl( size );
			break; 
		} else if ( (pad.Buttons & PSP_CTRL_CIRCLE) && ipl_type ) {		
			printf("Flashing IPL...");

			if(pspIplUpdateClearIpl() < 0) {
				ErrorExit(5000,"\241\311\241\265\241\301\241\256 ipl\241\242\n");///|ErrorExit(5000,"Failed to clear ipl!\n");
			}

			if (pspIplUpdateSetIpl( ipl_block_large + 0x4000 , size ) < 0) {
				ErrorExit(5000,"\241\311\241\265\241\315\241\303 ipl\241\242\n");///|ErrorExit(5000,"Failed to write ipl!\n");
			}

			printf("\241\306\241\253\241\241\n");///|printf("Done.\n");
			break; 
		} else if (pad.Buttons & PSP_CTRL_RTRIGGER) {
			ErrorExit(2000,"\241\321\241\267\241\302\241\313\241\241\n");///|ErrorExit(2000,"Cancelled by user.\n");
		}

		sceKernelDelayThread(10000);
	}

	ErrorExit(5000,"\n\241\246\241\327\241\306\241\253\241\241 5\241\275\241\277\241\326\241\316\241\300\241\264...\n");///|ErrorExit(5000,"\nInstall complete. Restarting in 5 seconds...\n");

	return 0;
}
