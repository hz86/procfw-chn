#include <psptypes.h>

u8 msx[] = 
{
	//ASC 6*12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x30,0x78,0x78,0x78,0x30,0x00,0x00,0x00,0x00,
	0xFC,0xFC,0xFC,0xCC,0x84,0x84,0x84,0xCC,0xFC,0xFC,0xFC,0xFC,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x1C,0x0C,0x0C,0x14,0x10,0x30,0x48,0x48,0x30,0x00,0x00,
	0x00,0x38,0x44,0x44,0x38,0x10,0x7C,0x10,0x10,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x0C,0x34,0x2C,0x34,0x24,0x24,0x2C,0x6C,0x60,0x00,0x00,
	0x00,0x54,0x54,0x28,0x28,0x6C,0x28,0x28,0x54,0x54,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0xFC,0x10,0x10,0x10,0x10,0x10,
	0x00,0x04,0x0C,0x1C,0x3C,0x7C,0x3C,0x1C,0x0C,0x04,0x00,0x00,
	0x00,0x10,0x38,0x10,0x10,0x10,0x10,0x10,0x38,0x10,0x00,0x00,
	0x00,0x28,0x28,0x28,0x28,0x28,0x28,0x00,0x28,0x28,0x00,0x00,
	0x00,0x3C,0x54,0x54,0x54,0x34,0x14,0x14,0x14,0x14,0x3C,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0xFC,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0xF0,0x10,0x10,0x10,0x10,0x10,
	0x00,0x10,0x38,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x10,0x10,0x10,0x10,0x10,
	0x00,0x00,0x00,0x00,0x08,0x7C,0x08,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x20,0x7C,0x20,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,0x00,
	0x00,0x28,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x28,0x28,0xFC,0x28,0x50,0xFC,0x50,0x50,0x00,0x00,
	0x00,0x20,0x78,0xA8,0xA0,0x60,0x30,0x28,0xA8,0xF0,0x20,0x00,
	0x00,0x00,0x48,0xA8,0xB0,0x50,0x28,0x34,0x54,0x48,0x00,0x00,
	0x00,0x00,0x20,0x50,0x50,0x78,0xA8,0xA8,0x90,0x6C,0x00,0x00,
	0x00,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x04,0x00,
	0x00,0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x40,0x00,
	0x00,0x00,0x00,0x20,0xA8,0x70,0x70,0xA8,0x20,0x00,0x00,0x00,
	0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80,
	0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,
	0x00,0x08,0x10,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x00,
	0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00,
	0x00,0x00,0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x40,0x80,0xF8,0x00,0x00,
	0x00,0x00,0x70,0x88,0x08,0x30,0x08,0x08,0x88,0x70,0x00,0x00,
	0x00,0x00,0x10,0x30,0x50,0x50,0x90,0x78,0x10,0x18,0x00,0x00,
	0x00,0x00,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x70,0x00,0x00,
	0x00,0x00,0x70,0x90,0x80,0xF0,0x88,0x88,0x88,0x70,0x00,0x00,
	0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x70,0x88,0x88,0x88,0x70,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x88,0x78,0x08,0x48,0x70,0x00,0x00,
	0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x20,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x20,0x00,
	0x00,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x00,0x00,
	0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x40,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x40,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x20,0x00,0x20,0x00,0x00,
	0x00,0x00,0x70,0x88,0x98,0xA8,0xA8,0xB8,0x80,0x78,0x00,0x00,
	0x00,0x00,0x20,0x20,0x30,0x50,0x50,0x78,0x48,0xCC,0x00,0x00,
	0x00,0x00,0xF0,0x48,0x48,0x70,0x48,0x48,0x48,0xF0,0x00,0x00,
	0x00,0x00,0x78,0x88,0x80,0x80,0x80,0x80,0x88,0x70,0x00,0x00,
	0x00,0x00,0xF0,0x48,0x48,0x48,0x48,0x48,0x48,0xF0,0x00,0x00,
	0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x48,0xF8,0x00,0x00,
	0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x40,0xE0,0x00,0x00,
	0x00,0x00,0x38,0x48,0x80,0x80,0x9C,0x88,0x48,0x30,0x00,0x00,
	0x00,0x00,0xCC,0x48,0x48,0x78,0x48,0x48,0x48,0xCC,0x00,0x00,
	0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00,
	0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0xE0,0x00,
	0x00,0x00,0xEC,0x48,0x50,0x60,0x50,0x50,0x48,0xEC,0x00,0x00,
	0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x44,0xFC,0x00,0x00,
	0x00,0x00,0xD8,0xD8,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8,0x00,0x00,
	0x00,0x00,0xDC,0x48,0x68,0x68,0x58,0x58,0x48,0xE8,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00,
	0x00,0x00,0xF0,0x48,0x48,0x70,0x40,0x40,0x40,0xE0,0x00,0x00,
	0x00,0x00,0x70,0x88,0x88,0x88,0x88,0xE8,0x98,0x70,0x18,0x00,
	0x00,0x00,0xF0,0x48,0x48,0x70,0x50,0x48,0x48,0xEC,0x00,0x00,
	0x00,0x00,0x78,0x88,0x80,0x60,0x10,0x08,0x88,0xF0,0x00,0x00,
	0x00,0x00,0xF8,0xA8,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00,
	0x00,0x00,0xCC,0x48,0x48,0x48,0x48,0x48,0x48,0x30,0x00,0x00,
	0x00,0x00,0xCC,0x48,0x48,0x50,0x50,0x30,0x20,0x20,0x00,0x00,
	0x00,0x00,0xA8,0xA8,0xA8,0x70,0x50,0x50,0x50,0x50,0x00,0x00,
	0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x50,0x50,0xD8,0x00,0x00,
	0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x20,0x20,0x70,0x00,0x00,
	0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x40,0x48,0xF8,0x00,0x00,
	0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38,0x00,
	0x00,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x00,0x00,
	0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00,
	0x00,0x20,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,
	0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x38,0x48,0x3C,0x00,0x00,
	0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0x70,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x40,0x40,0x38,0x00,0x00,
	0x00,0x00,0x18,0x08,0x08,0x38,0x48,0x48,0x48,0x3C,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x78,0x40,0x38,0x00,0x00,
	0x00,0x00,0x1C,0x20,0x20,0x78,0x20,0x20,0x20,0x78,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x3C,0x48,0x30,0x40,0x78,0x44,0x38,
	0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0xEC,0x00,0x00,
	0x00,0x00,0x20,0x00,0x00,0x60,0x20,0x20,0x20,0x70,0x00,0x00,
	0x00,0x00,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0xE0,
	0x00,0x00,0xC0,0x40,0x40,0x5C,0x50,0x70,0x48,0xEC,0x00,0x00,
	0x00,0x00,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xF0,0xA8,0xA8,0xA8,0xA8,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0xEC,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x30,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0x70,0x40,0xE0,
	0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x48,0x48,0x38,0x08,0x1C,
	0x00,0x00,0x00,0x00,0x00,0xD8,0x60,0x40,0x40,0xE0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x78,0x40,0x30,0x08,0x78,0x00,0x00,
	0x00,0x00,0x00,0x20,0x20,0x70,0x20,0x20,0x20,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xD8,0x48,0x48,0x48,0x3C,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xA8,0xA8,0x70,0x50,0x50,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xD8,0x50,0x20,0x50,0xD8,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x20,0xC0,
	0x00,0x00,0x00,0x00,0x00,0x78,0x10,0x20,0x20,0x78,0x00,0x00,
	0x00,0x18,0x10,0x10,0x10,0x20,0x10,0x10,0x10,0x10,0x18,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x60,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x60,0x00,
	0x40,0xA4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	//自定义 超出范围显示
	0xFF,0xE0,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0xFF,0xE0,0x00,0x00,

	//自定义
	0x00,0x00,0x30,0x00,0x78,0x00,0x78,0x00,0x78,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x0C,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
	0x04,0x00,0x7F,0xE0,0x40,0x20,0x88,0x40,0x08,0x00,0xFF,0xE0,0x11,0x00,0x19,0x00,0x06,0x00,0x0D,0x80,0xF0,0x60,0x00,0x00,
	0x22,0x00,0x23,0xE0,0xF4,0x20,0x27,0xA0,0x2C,0xA0,0x74,0xA0,0xA7,0xA0,0x24,0x40,0x24,0x20,0x24,0x20,0xE7,0xE0,0x00,0x00,
	0xFF,0xE0,0x02,0x00,0x04,0x00,0x04,0x00,0x0D,0x00,0x14,0x80,0x24,0x40,0xC4,0x20,0x04,0x00,0x04,0x00,0x04,0x00,0x00,0x00,
	0x37,0xC0,0xE4,0x40,0x24,0x40,0xF7,0xC0,0x20,0x00,0x6F,0xE0,0x71,0x00,0xA7,0xC0,0xA1,0x00,0x21,0x00,0x2F,0xE0,0x00,0x00,
	0x21,0x00,0x2F,0xE0,0xF1,0x00,0x21,0x00,0x2F,0xE0,0x30,0x80,0xEF,0xE0,0x28,0x80,0x24,0x80,0x20,0x80,0xE3,0x80,0x00,0x00,
	0x11,0x00,0x21,0x00,0xFB,0xE0,0x8A,0x20,0x8C,0x20,0x8A,0x20,0xF9,0x20,0x89,0x20,0x88,0x20,0xF8,0x20,0x89,0xC0,0x00,0x00,
	0x41,0x00,0x21,0x00,0x2F,0xE0,0x81,0x00,0x41,0x00,0x1F,0xE0,0x42,0x00,0x42,0x80,0xC4,0x40,0x49,0xE0,0x4E,0x20,0x00,0x00,
	0x04,0x00,0x0A,0x00,0x11,0x00,0x24,0x80,0xC4,0x60,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x00,0x00,
	0x20,0x00,0x7B,0xE0,0x51,0x20,0xFE,0xE0,0x54,0x80,0x7F,0xE0,0x54,0x80,0x7F,0xE0,0x54,0x80,0x94,0x80,0x9C,0x80,0x00,0x00,
	0x12,0x00,0x14,0x00,0x27,0xE0,0x68,0x20,0xB1,0x00,0x25,0x40,0x25,0x40,0x29,0x20,0x31,0x20,0x21,0x00,0x27,0x00,0x00,0x00,
	0x49,0x00,0xFD,0x00,0x51,0xE0,0xFE,0x20,0x54,0x80,0xFE,0x80,0x54,0x80,0xFC,0x80,0x59,0x40,0xD5,0x40,0x52,0x20,0x00,0x00,
	0x7F,0xC0,0x04,0x00,0x04,0x00,0x04,0x00,0xFF,0xE0,0x0A,0x00,0x0A,0x00,0x12,0x00,0x12,0x20,0x22,0x20,0xC3,0xE0,0x00,0x00,
	0x04,0x00,0x7F,0xE0,0x40,0x00,0x5F,0x80,0x45,0x00,0x42,0x00,0x7F,0xE0,0x42,0x40,0x42,0x00,0x82,0x00,0x8E,0x00,0x00,0x00,
	0x7F,0xE0,0x40,0x00,0x44,0x00,0x44,0x00,0x44,0x00,0x5F,0xC0,0x45,0x00,0x44,0x80,0x44,0x40,0x84,0x00,0xBF,0xE0,0x00,0x00,
	0x42,0x00,0x21,0x00,0x1F,0xE0,0x00,0x80,0xCC,0x80,0x43,0x00,0x41,0x00,0x42,0x80,0x6C,0x40,0x90,0x00,0x0F,0xE0,0x00,0x00,
	0x04,0x00,0x04,0x40,0xFF,0xE0,0x04,0x00,0x3F,0x80,0x10,0x80,0x11,0x00,0x0A,0x00,0x04,0x00,0x1B,0x00,0xE0,0xE0,0x00,0x00,
	0x11,0x00,0x91,0x00,0x5F,0xE0,0x31,0x00,0xD7,0xC0,0x14,0x00,0xFF,0xE0,0x0A,0x40,0x32,0x80,0xD5,0x00,0x18,0xE0,0x00,0x00,
};
