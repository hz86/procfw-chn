#include <stdio.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspsysclib.h>
#include <string.h>

#include "printf_chs.h"
#include "font_chs.c"

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512

static int X = 0, Y = 0;
static int MX=80, MY=22;
static u32 bg_col = 0, fg_col = 0xFFFFFFFF;
static int bg_enable = 1;
static void* g_vram_base = (u32 *) 0x04000000;
static int g_vram_offset = 0;
static int g_vram_mode = PSP_DISPLAY_PIXEL_FORMAT_8888;
static int init = 0;
static int clearline_en = 1;

static u16 _convert_8888_to_565(u32 color)
{
	int r, g, b;

	b = (color >> 19) & 0x1F;
	g = (color >> 10) & 0x3F;
	r = (color >> 3) & 0x1F;

	return r | (g << 5) | (b << 11);
}

static u16 _convert_8888_to_5551(u32 color)
{
	int r, g, b, a;

	a = (color >> 24) ? 0x8000 : 0;
	b = (color >> 19) & 0x1F;
	g = (color >> 11) & 0x1F;
	r = (color >> 3) & 0x1F;

	return a | r | (g << 5) | (b << 10);
}

static u16 _convert_8888_to_4444(u32 color)
{
	int r, g, b, a;

	a = (color >> 28) & 0xF; 
	b = (color >> 20) & 0xF;
	g = (color >> 12) & 0xF;
	r = (color >> 4) & 0xF;

	return (a << 12) | r | (g << 4) | (b << 8);
}

static void _clear_screen_16(u16 color)
{
	int x;
	u16 *vram = g_vram_base;
   
	vram += (g_vram_offset >> 1);

	for(x = 0; x < (PSP_LINE_SIZE * PSP_SCREEN_HEIGHT); x++)
	{
		*vram++ = color; 
	}
}

static void _clear_screen_32(u32 color)
{
	int x;
	u32 *vram = g_vram_base;
	vram +=	(g_vram_offset>>2);

	for(x = 0; x < (PSP_LINE_SIZE * PSP_SCREEN_HEIGHT); x++)
	{
		*vram++ = color; 
	}
}

static void _clear_screen(u32 color)
{
	if(g_vram_mode == PSP_DISPLAY_PIXEL_FORMAT_8888)
	{
		_clear_screen_32(color);
	}
	else
	{
		u16 c = 0;
		switch(g_vram_mode)
		{
			case PSP_DISPLAY_PIXEL_FORMAT_565: c = _convert_8888_to_565(color);
				break;
			case PSP_DISPLAY_PIXEL_FORMAT_5551: c = _convert_8888_to_5551(color);
				break;
			case PSP_DISPLAY_PIXEL_FORMAT_4444: c = _convert_8888_to_4444(color);
				break;
		};
		_clear_screen_16(c);
	}
}

void CHS_ScreenInitEx(void *vram_base, int mode, int setup)
{
	switch(mode)
	{
		case PSP_DISPLAY_PIXEL_FORMAT_565:
		case PSP_DISPLAY_PIXEL_FORMAT_5551:
		case PSP_DISPLAY_PIXEL_FORMAT_4444:
		case PSP_DISPLAY_PIXEL_FORMAT_8888:
			break;
		default: mode = PSP_DISPLAY_PIXEL_FORMAT_8888;
	};

	X = Y = 0;
	/* Place vram in uncached memory */
	if(vram_base == NULL)
	{
		vram_base = (void*) (0x40000000 | (u32) 0x04000000);
	}
	g_vram_base = vram_base;
	g_vram_offset = 0;
	g_vram_mode = mode;
	if(setup)
	{
		sceDisplaySetMode(0, PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT);
		sceDisplaySetFrameBuf((void *) g_vram_base, PSP_LINE_SIZE, mode, 1);
	}
	_clear_screen(bg_col);
	init = 1;
}

void CHS_ScreenInit(void)
{
	X = Y = 0;
	CHS_ScreenInitEx(NULL, PSP_DISPLAY_PIXEL_FORMAT_8888, 1);
}

void CHS_ScreenEnableBackColor(int enable) 
{
	bg_enable = enable;
}

void CHS_ScreenSetBackColor(u32 colour)
{
	bg_col = colour;
}

void CHS_ScreenSetTextColor(u32 colour)
{
	fg_col = colour;
}

void CHS_ScreenSetColorMode(int mode)
{
	switch(mode)
	{
		case PSP_DISPLAY_PIXEL_FORMAT_565:
		case PSP_DISPLAY_PIXEL_FORMAT_5551:
		case PSP_DISPLAY_PIXEL_FORMAT_4444:
		case PSP_DISPLAY_PIXEL_FORMAT_8888:
			break;
		default: mode = PSP_DISPLAY_PIXEL_FORMAT_8888;
	};

	g_vram_mode = mode;
}

void CHS_ScreenSetMaxX(unsigned int maxx)
{
	MX = maxx;
}

void CHS_ScreenSetMaxY(unsigned int maxy)
{
	MY = maxy;
}

int CHS_ScreenGetX(void)
{
	return X;
}

int CHS_ScreenGetY(void)
{
	return Y;
}

void _CHS_ScreenClearLine( int Y)
{
	if(clearline_en)
	{
		int i;
		if(bg_enable)
		{
			for (i=0; i < MX; i++)
			{
				CHS_ScreenPutChar( i*6 , Y * 12, bg_col, ' ', 0);
			}
		}
	}
	return;
}

void CHS_ScreenClear(void)
{
	int y;

	if(init)
	{
		for(y=0;y<MY;y++)
		{
			_CHS_ScreenClearLine(y);
		}
		CHS_ScreenSetXY(0,0);
		_clear_screen(bg_col);
	}
}

void CHS_ScreenSetXY(int x, int y)
{
	if( x<MX && x>=0 ) X=x;
	if( y<MY && y>=0 ) Y=y;
}

void CHS_ScreenSetOffset(int offset)
{
	g_vram_offset = offset;
}

void CHS_ScreenSetBase(u32* base)
{
	g_vram_base = base;
}

static void _PutPixel(int x, int y, u32 color)
{
	u32 *vram_ptr;

	vram_ptr = g_vram_base;
	if(g_vram_mode == PSP_DISPLAY_PIXEL_FORMAT_8888)
	{
		vram_ptr += (g_vram_offset >> 2) + x;
	}
	else
	{
		u16 c = 0;
		u16 b = 0;
		switch(g_vram_mode)
		{
			case PSP_DISPLAY_PIXEL_FORMAT_565: c = _convert_8888_to_565(color);
				b = _convert_8888_to_565(bg_col);
				break;
			case PSP_DISPLAY_PIXEL_FORMAT_5551: c = _convert_8888_to_5551(color);
				b = _convert_8888_to_5551(bg_col);
				break;
			case PSP_DISPLAY_PIXEL_FORMAT_4444: c = _convert_8888_to_4444(color);
				b = _convert_8888_to_4444(bg_col);
				break;
		};
		vram_ptr += (g_vram_offset >> 1) + x;
	}
	vram_ptr += (y * PSP_LINE_SIZE);

	*vram_ptr = color;
}

void CHS_ScreenPutChar( int x, int y, u32 color, u8 ch1, u8 ch2)
{
	int i,j,font_offset;
	u8 *font;

	if(init)
	{
		if((int)ch1 < 128)
		{
			font = &msx[ (int)ch1 * 12 ];
			for (i=0; i < 12; i++, font++)
			{
				for (j=0; j < 6; j++)
				{
					if ((*font & (128 >> j)))
						_PutPixel(x+j, y+i, color);
					else if(bg_enable)
						_PutPixel(x+j, y+i, bg_col);
				}
			}
		}
		else
		{
			if( ((int)ch1 >= 0xA1) && ((int)ch1 <= 0xFE) && ((int)ch2 >= 0xA1) && ((int)ch2 <= 0xFE) )
				font_offset = 1536 + 24 + ((94*((int)ch1-0xA1)+((int)ch2-0xA1))*24);
			else
				font_offset = 1536;

			if(font_offset+24 > sizeof(msx))
				font_offset = 1536;

			font = &msx[ font_offset ];
			for (i=0; i < 12; i++, font+=2)
			{
				for (j=0; j < 12; j++)
				{
					if (j < 8)
					{
						if ((*font & (128 >> j)))
							_PutPixel(x+j, y+i, color);
						else if(bg_enable)
							_PutPixel(x+j, y+i, bg_col);
					}
					else
					{
						if ((*(font+1) & (128 >> (j-8))))
							_PutPixel(x+j, y+i, color);
						else if(bg_enable)
							_PutPixel(x+j, y+i, bg_col);
					}
				}
			}
		}
	}
}

void CHS_ScreenClearLineEnable(void)
{
	clearline_en = 1;
	return;
}

void CHS_ScreenClearLineDisable(void)
{
	clearline_en = 0;
	return;
}

int CHS_ScreenPrintData(const char *buff, int size)
{
	int i = 0;
	int j;
	unsigned char c[2];

	if(init)
	{
		while (i < size)
		{
			c[0] = buff[i];
			if (c[0] < 128)
			{
				c[1] = 0;
				i++;

				switch (c[0])
				{
					case '\r':
						X = 0;
						break;
					case '\n':
						X = 0;
						Y ++;
						if (Y >= MY)
							Y = 0;
						_CHS_ScreenClearLine(Y);
						break;
					case '\t':
						for (j = 0; j < 5 && X < MX; j++)
						{
							CHS_ScreenPutChar( X*6 , Y * 12, fg_col, ' ', 0);
							X++;
						}
						break;
					default:
						if (X+1 > MX)
						{
							X = 0;
							Y++;
							if (Y >= MY)
								Y = 0;
							_CHS_ScreenClearLine(Y);
						}
						CHS_ScreenPutChar( X*6 , Y * 12, fg_col, c[0], c[1]);
						X++;
				}
			}
			else
			{
				c[1] = buff[i+1];
				i+=2;

				if (X+2 > MX)
				{
					X = 0;
					Y++;
					if (Y >= MY)
						Y = 0;
					_CHS_ScreenClearLine(Y);
				}
				CHS_ScreenPutChar( X*6 , Y * 12, fg_col, c[0], c[1]);
				X+=2;
			}
		}
	}
	return i;
}

int CHS_ScreenPuts(const char *str)
{
	return CHS_ScreenPrintData(str, strlen(str));
}

void CHS_ScreenPrintf(char *format, ...)
{
	va_list opt;
	char buff[2048];
	int bufsz;
   
	va_start(opt, format);
	bufsz = vsnprintf( buff, (size_t) sizeof(buff), format, opt);
	va_end(opt);
	(void) CHS_ScreenPrintData(buff, bufsz);
}

