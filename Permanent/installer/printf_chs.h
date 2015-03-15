#ifndef _PRINTF_CHS_H_
#define _PRINTF_CHS_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Debug Debug Utility Library */

/** @addtogroup Debug */
/*@{*/

/** 
  * Initialise the debug screen
  */
void CHS_ScreenInit(void);

/**
 * Extended debug screen init
 *
 * @param vram_base - Base address of frame buffer, if NULL then sets a default
 * @param mode - Colour mode
 * @param setup - Setup the screen if 1
 */
void CHS_ScreenInitEx(void *vram_base, int mode, int setup);

/**
  * Do a printf to the debug screen.
  *
  * @param fmt - Format string to print
  * @param ... - Arguments
  */
void CHS_ScreenPrintf(char *fmt, ...) __attribute__((format(printf,1,2)));

/**
 * Enable or disable background colour writing (defaults to enabled)
 * 
 * @param enable - Set 1 to to enable background color, 0 for disable
 */
void CHS_ScreenEnableBackColor(int enable);

/** 
  * Set the background color for the text
  * @note To reset the entire screens bg colour you need to call pspDebugScreenClear
  *
  * @param color - A 32bit RGB colour
  */
void CHS_ScreenSetBackColor(u32 color);

/**
  * Set the text color 
  *
  * @param color - A 32 bit RGB color
  */
void CHS_ScreenSetTextColor(u32 color);

/**
 * Set the color mode (you must have switched the frame buffer appropriately)
 *
 * @param mode - Color mode
 */
void CHS_ScreenSetColorMode(int mode);

/** 
  * Draw a single character to the screen.
  *
  * @param x - The x co-ordinate to draw to (pixel units)
  * @param y - The y co-ordinate to draw to (pixel units)
  * @param color - The text color to draw
  * @param ch - The character to draw
  */
void CHS_ScreenPutChar(int x, int y, u32 color, u8 ch1, u8 ch2);

/**
  * Set the current X and Y co-ordinate for the screen (in character units)
  */
void CHS_ScreenSetXY(int x, int y);

/**
  * Set the video ram offset used for the screen
  *
  * @param offset - Offset in bytes
  */
void CHS_ScreenSetOffset(int offset);

/**
 * Set the video ram base used for the screen
 *
 * @param base - Base address in bytes
 */
void CHS_ScreenSetBase(u32* base);

/**
 * Set the X maximum coordinate (in character units)
 * @note Thus line length will be X + 1 characters.
 *
 * @param maxx - The X maximum coordinate 
 */
void CHS_ScreenSetMaxX(unsigned int maxx);

/**
 * Set the Y maximum coordinate (in character units)
 *
 * @param maxx - The X maximum coordinate 
 */
void CHS_ScreenSetMaxY(unsigned int maxy);

/** 
  * Get the current X co-ordinate (in character units)
  *
  * @return The X co-ordinate
  */
int CHS_ScreenGetX(void);

/** 
  * Get the current Y co-ordinate (in character units)
  *
  * @return The Y co-ordinate
  */
int CHS_ScreenGetY(void);

/**
  * Clear the debug screen.
  */
void CHS_ScreenClear(void);

/**
  * Print non-nul terminated strings.
  * 
  * @param buff - Buffer containing the text.
  * @param size - Size of the data
  *
  * @return The number of characters written
  */
int CHS_ScreenPrintData(const char *buff, int size);

/**
 * Print a string
 *
 * @param str - String
 *
 * @return The number of characters written
 */
int CHS_ScreenPuts(const char *str);

/**
 * Enable the clear line function that allows debug to clear the screen
*/
void CHS_ScreenClearLineEnable(void);

/**
 * Disable the clear line function that causes flicker on constant refreshes
*/
void CHS_ScreenClearLineDisable(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
