
#ifndef DEF_H_
#define DEF_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdint.h>

//#define KBD_USE_INIT

//#define USE_ST7735
//#define USE_ST7789
#define USE_SSD1306

#ifdef USE_ST7735
#define DISPLAY_DRIVER_FILE				"device/st7735.h"
#endif
#ifdef USE_ST7789
#define DISPLAY_DRIVER_FILE				"device/st7789.h"
#endif
#ifdef USE_SSD1306
#define DISPLAY_DRIVER_FILE				"device/ssd1306.h"
#endif

#define IMPLEMENTED
//#define USE_DESIGN_UPGRADE
#define GUI_EXPLORER

#define MAX_DISK_NR						1
//#define SSD1306_USE_NO_BUF
//#define ST7735S_128x128
//#define ST7735_BW_MODE

#define MAX_ALLOWED_PATH_LEN_BUF		64
#define MAX_ALLOWED_FILE_NAME_LEN_BUF	32

#include "def_arduboy_mega.h"

/*********************************************************************************************************************************/

#ifdef USE_ST7735
#define DISPLAY_FUNC_INIT(spi, screen_buf)																			st7735_init(spi, screen_buf)
#define DISPLAY_FUNC_GET_X()																						st7735_get_x()
#define DISPLAY_FUNC_GET_Y()																						st7735_get_y()
#define DISPLAY_FUNC_CLEAR(inst, buf, inkColor)																		st7735_clear(inst, buf, inkColor);
#define DISPLAY_FUNC_DRAW_PIXEL(inst, box, buf, x, y, inkColor)														st7735_draw_pixel(inst, box, buf, x, y, inkColor)
#define DISPLAY_FUNC_DRAW_RECTANGLE(inst, box, buf, x, y, x_size, y_size, fill, inkColor)							st7735_draw_rectangle(inst, box, buf, x, y, x_size, y_size, fill, inkColor)
#define DISPLAY_FUNC_DRAW_STRING(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)			st7735_draw_string(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)
//#define DISPLAY_FUNC_DRAW_LINE(inst, box, buf, x1, y1, x2, y2, inkColor)											st7735_draw_line(inst, box, buf, x1, y1, x2, y2, inkColor)
#define DISPLAY_FUNC_DRAW_H_LINE(inst, box, buf, x1, x2, y, width, inkColor)										st7735_draw_h_line(inst, box, buf, x1, x2, y, width, inkColor)
#define DISPLAY_FUNC_DRAW_V_LINE(inst, box, buf, y1, y2, x, width, inkColor)										st7735_draw_v_line(inst, box, buf, y1, y2, x, width, inkColor)
#define DISPLAY_COLOR_VAR                                                                                           bool
#define DISPLAY_VRAM_TYPE                                                                                           uint8_t

#define GUI_UPPER_LIMIT_ROW																							0
#define GUI_LOWER_LIMIT_ROW																							9
#endif
#ifdef USE_ST7789
#define DISPLAY_FUNC_INIT(spi, screen_buf)																			st7789_init(spi, screen_buf)
#define DISPLAY_FUNC_GET_X()																						st7789_get_x()
#define DISPLAY_FUNC_GET_Y()																						st7789_get_y()
#define DISPLAY_FUNC_CLEAR(inst, buf, inkColor)																		st7789_clear(inst, buf, inkColor);
#define DISPLAY_FUNC_DRAW_PIXEL(inst, box, buf, x, y, inkColor)														st7789_draw_pixel(inst, box, buf, x, y, inkColor)
#define DISPLAY_FUNC_DRAW_RECTANGLE(inst, box, buf, x, y, x_size, y_size, fill, inkColor)							st7789_draw_rectangle(inst, box, buf, x, y, x_size, y_size, fill, inkColor)
#define DISPLAY_FUNC_DRAW_STRING(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)			st7789_draw_string(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)
//#define DISPLAY_FUNC_DRAW_LINE(inst, box, buf, x1, y1, x2, y2, inkColor)											st7789_draw_line(inst, box, buf, x1, y1, x2, y2, inkColor)
#define DISPLAY_FUNC_DRAW_H_LINE(inst, box, buf, x1, x2, y, width, inkColor)										st7789_draw_h_line(inst, box, buf, x1, x2, y, width, inkColor)
#define DISPLAY_FUNC_DRAW_V_LINE(inst, box, buf, y1, y2, x, width, inkColor)										st7789_draw_v_line(inst, box, buf, y1, y2, x, width, inkColor)
#define DISPLAY_COLOR_VAR                                                                                           bool
#define DISPLAY_VRAM_TYPE                                                                                           uint8_t

#define GUI_UPPER_LIMIT_ROW																							0
#define GUI_LOWER_LIMIT_ROW																							29
#endif
#ifdef USE_SSD1306
#define DISPLAY_FUNC_INIT(spi, screen_buf)																			ssd1306_init(spi, screen_buf)
#define DISPLAY_FUNC_GET_X()																						ssd1306_get_x()
#define DISPLAY_FUNC_GET_Y()																						ssd1306_get_y()
#define DISPLAY_FUNC_CLEAR(inst, buf, inkColor)																		ssd1306_clear(inst, buf, inkColor);
#define DISPLAY_FUNC_DRAW_PIXEL(inst, box, buf, x, y, inkColor)														ssd1306_draw_pixel(inst, box, buf, x, y, inkColor)
#define DISPLAY_FUNC_DRAW_RECTANGLE(inst, box, buf, x, y, x_size, y_size, fill, inkColor)							ssd1306_draw_rectangle(inst, box, buf, x, y, x_size, y_size, fill, inkColor)
#define DISPLAY_FUNC_DRAW_STRING(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)			ssd1306_draw_string(inst, box, buf, string, x, y, terminalMode, wordWrap, foreColor, inkColor)
//#define DISPLAY_FUNC_DRAW_LINE(inst, box, buf, x1, y1, x2, y2, inkColor)											ssd1306_draw_line(inst, box, buf, x1, y1, x2, y2, inkColor)
#define DISPLAY_FUNC_DRAW_H_LINE(inst, box, buf, x1, x2, y, width, inkColor)										ssd1306_draw_h_line(inst, box, buf, x1, x2, y, width, inkColor)
#define DISPLAY_FUNC_DRAW_V_LINE(inst, box, buf, y1, y2, x, width, inkColor)										ssd1306_draw_v_line(inst, box, buf, y1, y2, x, width, inkColor)
#define DISPLAY_REFRESH(inst, buf)                                                                                  ssd1306_rfsh(inst, buf)
#define DISPLAY_COLOR_VAR                                                                                           bool
#define DISPLAY_VRAM_TYPE                                                                                           uint8_t

#define GUI_UPPER_LIMIT_ROW																							0
#define GUI_LOWER_LIMIT_ROW																							7
#endif

#define GUI_APP_FILE_INCLUDE																						"app-sec-boot.h"
#define GUI_LIST_OF_DISPLAYED_EXTENSIONS																			{"APP"} // Upper cases
#define GUI_ACT_FUNC_ON_FILE_SELECT(uSD, spi_screen, screen_buf)													app_app_load(uSD, spi_screen, screen_buf)
#define GUI_ACT_FUNC_ON_FS_MOUNTED(uSD, spi_screen, screen_buf)														app_fs_mounted(uSD, spi_screen, screen_buf)
//#define GUI_ACT_FUNC_ON_LEFT_BTN_PRESS(uSD, spi_screen, screen_buf)												app_left(uSD, spi_screen, screen_buf)
//#define GUI_ACT_FUNC_ON_RIGHT_BTN_PRESS(uSD, spi_screen, screen_buf)												app_right(uSD, spi_screen, screen_buf)


/*******************************************/
#endif /* DEF_H_ */
