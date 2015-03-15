#include "common.h"

const char *g_messages_cht[] = {
	"默认",
	"禁用",
	"启用",
	"标准",
	"M33 driver",
	"Sony NP9660",
	"Inferno",
	"CPU 频率(XMB) ",
	"CPU 频率(GAME)",
	"USB 设备      ",
	"UMD ISO 模式  ",
	"挂载ISO VIDEO ",
	"恢复菜单  ->",
	"关闭设备",
	"挂起设备",
	"重启设备",
	"重启VSH ",
	"退出",
	"PRO VSH菜单",
	"Flash",
	"UMD Disc",
	"Memory Stick",
	"无",
};

u8 message_test_cht[NELEMS(g_messages_cht) == MSG_END ? 0 : -1];
