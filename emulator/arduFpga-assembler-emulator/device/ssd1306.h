#ifndef SSD1306_H
#define SSD1306_H

#include <stdbool.h>
#include "driver/spi.h"
#include "gfx/draw.h"

void ssd1306_init(spi_t *inst, uint8_t *buf);
void ssd1306_wr_cmd(spi_t *inst, uint8_t cmd);
uint16_t ssd1306_get_x(void);
uint16_t ssd1306_get_y(void);
void ssd1306_rfsh(spi_t *inst, uint8_t *buf);
void ssd1306_on(spi_t *inst, bool state);
void ssd1306_set_contrast(spi_t *inst, uint8_t cont);
void ssd1306_draw_pixel(spi_t *inst, box_t *box, uint8_t *buf, int16_t x, int16_t y, bool state);
void ssd1306_draw_rectangle(spi_t *inst, box_t *box, uint8_t *buf, int16_t x, int16_t y, int16_t x_size, int16_t y_size, bool fill, bool state);
void ssd1306_draw_h_line(spi_t *inst, box_t *box, uint8_t *buf, int16_t x1, int16_t x2, int16_t y, uint8_t width, bool state);
void ssd1306_draw_v_line(spi_t *inst, box_t *box, uint8_t *buf, int16_t y1, int16_t y2, int16_t x, uint8_t width, bool state);
void ssd1306_clear(spi_t *inst, uint8_t *buf, bool state);
int ssd1306_draw_string(spi_t *inst, box_t *box, uint8_t *buf, char *string, int16_t x, int16_t y, bool terminalMode, bool wordWrap, bool foreColor, bool inkColor);

#endif // SSD1306_H
