#include "systemctrl.h"
#include "systemctrl_se.h"
#include "utils.h"
#include "main.h"

const char * g_messages_chs[] = {
	"PRO \241\327\241\304\241\254\241\270",
	"\242\341\241\254\241\270",
	"\241\342\242\251\242\335",
	"\242\271\241\264\242\335",
	"\241\300\241\330",
	"\241\364\242\247",
	"\241\376\242\322",
	"\241\343\242\322",
	"\242\243\241\326USB",
	"\241\376\242\322USB",
	"\241\343\242\322USB",
	"\241\332\241\246\242\254\242\333",
	"\242\245\242\324\241\374\241\371",
	"\241\327\241\304\241\254\241\270\242\347\242\267",
	"ISO \241\362\242\261",
	"\241\250\242\345",
	"M33 driver",
	"Sony NP9660",
	"Inferno",
	"USB \242\254\241\245",
	"Flash 0",
	"Flash 1",
	"Flash 2",
	"Flash 3",
	"UMD Disc",
	"\241\351\241\340 USB\242\256\241\311\241\273\241\262\241\263\241\273 (PSP-1000\242\275\242\303)",
	"\242\257\242\322Slim\242\313\242\252 (PSP-1000\242\343\242\322)",
	"\242\257\242\322htmlviewer\242\346\241\275\242\316\241\244\241\266\242\273\242\333",
	"\242\320\241\255 MAC\241\272\242\331",
	"\241\376\241\276\242\256\242\270\241\317Sony Logo",
	"\242\270\241\317\242\323\242\300\241\376\241\276\241\324\241\360",
	"\242\323\242\300\241\352\241\251\242\335\242\320\241\255PIC0.PNG\241\321PIC1.PNG",
	"\241\244\241\323 USB\242\254\241\245\241\241\242\344Flash",
	"\242\257\242\322/seplugins/version.txt",
	"\242\257\242\322/seplugins/usbversion.txt",
	"\242\257\242\322\242\346\241\275\242\316\241\312\242\304\241\303\242\276\242\241",
	"\242\350\242\332\242\253\241\265\242\307\241\357\242\274\241\336 (PSP-Go\242\343\242\322)",
	"\241\307\241\334\242\254\242\333",
	"\241\260\241\336(XMB)",
	"\241\260\241\336(Game)",
	"\241\260\241\336(Pops)",
	"NoDRM \242\317\242\244",
	"\242\323\242\300\242\256\242\320\241\255 CFW\242\274\241\336",
	"\242\323\242\300\242\256\241\343\242\322\242\314\241\305",
	"\241\344\241\260\241\336\242\330\241\261(PSP-Go\242\343\242\322)",
	"Inferno & NP9660 \242\257\242\322ISO\241\307\242\265\241\325\241\266",
	"Inferno & NP9660 \241\325\241\266\241\267\242\302(MB)",
	"Inferno & NP9660 \241\325\241\266\242\263",
	"Inferno & NP9660 \241\325\241\266\241\256\241\354",
	"\242\325\242\311\241\301latin1\241\271ISO\242\274\241\336\241\361",
	"Memory Stick\241\335\242\265",
	"\242\275",
	"Pop",
	"Game",
	"Vsh",
	"Pop & Game",
	"Game & Vsh",
	"Vsh & Pop",
	"\242\260\242\336",
	"CPU \241\372\241\353",
	"CPU/BUS(XMB) ",
	"CPU/BUS(Game)",
	"\241\260\241\336\241\315\241\347",
	"System Storage",
	"Memory Stick",
	"\241\260\241\336\242\327System Storage",
	"\241\260\241\336\242\327Memory Stick",
	"\242\342\241\257\241\251\241\373\241\341",
	"WMA \241\333\241\331",
	"Flash \241\333\241\331",
	"\241\242\241\367\241\337\241\326",
	"\242\246\242\247\241\242\241\367: X",
	"\242\246\242\247\241\242\241\367: O",
	"\241\333\241\331 WMA",
	"\241\333\241\331 Flash",
	"\241\337\241\326 O/X\241\242\241\367",
	"\241\337\241\326 O/X\241\242\241\367 (\242\310\242\337\241\376 VSH\241\322\241\253\241\366\242\255\242\303)",
	"\242\253\241\265\242\307\241\357\242\274\241\336 (PSP-Go\242\343\242\322)",
	"\242\307\241\357\242\274\241\336\242\253\241\265",
	"\242\326\242\306/PSP/GAME/RECOVERY/EBOOT.PBP",
	"\241\314\241\247\242\254\241\245",
	"\241\313\241\375\242\254\241\245",
	"\242\337\241\376\242\254\241\245",
	"\242\337\241\376VSH",
	"\241\302\242\315",
	"\242\250\241\246",
	"\241\356\241\316",
	"\241\370\242\340",
	"\241\320\241\316",
	"\242\321\241\316",
	"\241\363\242\277\241\310",
	"\241\243\241\267\241\350\242\312",
	"\242\301\241\306",
	"\242\266\242\272",
	"\241\277\241\355\242\264",
	"\242\335\241\316",
	"\241\274\242\262\241\346\242\305I",
	"\241\274\242\262\241\346\242\305II",
	"\242\242\242\334\241\307\242\273\241\365\241\266\241\252\241\345",
	"\242\257\242\322/seplugins/mac.txt",
};

u8 message_test_chs[NELEMS(g_messages_chs) == MSG_END ? 0 : -1];
