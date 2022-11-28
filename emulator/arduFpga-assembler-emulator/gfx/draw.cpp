
#include "draw.h"

#include DISPLAY_DRIVER_FILE

#define FIRST_CHAR_IDX      32


// Font Definition
#ifdef __AVR_MEGA__
const uint8_t font4x6[97][2] PROGMEM = {
#else
const uint8_t font4x6[97][2] = {
#endif
    { 0x00  ,  0x00 },   /*SPACE*/
    { 0x49  ,  0x08 },   /*'!'*/
    { 0xb4  ,  0x00 },   /*'"'*/
    { 0xbe  ,  0xf6 },   /*'#'*/
    { 0x7b  ,  0x7a },   /*'$'*/
    { 0xa5  ,  0x94 },   /*'%'*/
    { 0x55  ,  0xb8 },   /*'&'*/
    { 0x48  ,  0x00 },   /*'''*/
    { 0x29  ,  0x44 },   /*'('*/
    { 0x44  ,  0x2a },   /*')'*/
    { 0x15  ,  0xa0 },   /*'*'*/
    { 0x0b  ,  0x42 },   /*'+'*/
    { 0x00  ,  0x50 },   /*','*/
    { 0x03  ,  0x02 },   /*'-'*/
    { 0x00  ,  0x08 },   /*'.'*/
    { 0x25  ,  0x90 },   /*'/'*/
    { 0x76  ,  0xba },   /*'0'*/
    { 0x59  ,  0x5c },   /*'1'*/
    { 0xc5  ,  0x9e },   /*'2'*/
    { 0xc5  ,  0x38 },   /*'3'*/
    { 0x92  ,  0xe6 },   /*'4'*/
    { 0xf3  ,  0x3a },   /*'5'*/
    { 0x73  ,  0xba },   /*'6'*/
    { 0xe5  ,  0x90 },   /*'7'*/
    { 0x77  ,  0xba },   /*'8'*/
    { 0x77  ,  0x3a },   /*'9'*/
    { 0x08  ,  0x40 },   /*':'*/
    { 0x08  ,  0x50 },   /*';'*/
    { 0x2a  ,  0x44 },   /*'<'*/
    { 0x1c  ,  0xe0 },   /*'='*/
    { 0x88  ,  0x52 },   /*'>'*/
    { 0xe5  ,  0x08 },   /*'?'*/
    { 0x56  ,  0x8e },   /*'@'*/
    { 0x77  ,  0xb6 },   /*'A'*/
    { 0x77  ,  0xb8 },   /*'B'*/
    { 0x72  ,  0x8c },   /*'C'*/
    { 0xd6  ,  0xba },   /*'D'*/
    { 0x73  ,  0x9e },   /*'E'*/
    { 0x73  ,  0x92 },   /*'F'*/
    { 0x72  ,  0xae },   /*'G'*/
    { 0xb7  ,  0xb6 },   /*'H'*/
    { 0xe9  ,  0x5c },   /*'I'*/
    { 0x64  ,  0xaa },   /*'J'*/
    { 0xb7  ,  0xb4 },   /*'K'*/
    { 0x92  ,  0x9c },   /*'L'*/
    { 0xbe  ,  0xb6 },   /*'M'*/
    { 0xd6  ,  0xb6 },   /*'N'*/
    { 0x56  ,  0xaa },   /*'O'*/
    { 0xd7  ,  0x92 },   /*'P'*/
    { 0x76  ,  0xee },   /*'Q'*/
    { 0x77  ,  0xb4 },   /*'R'*/
    { 0x71  ,  0x38 },   /*'S'*/
    { 0xe9  ,  0x48 },   /*'T'*/
    { 0xb6  ,  0xae },   /*'U'*/
    { 0xb6  ,  0xaa },   /*'V'*/
    { 0xb6  ,  0xf6 },   /*'W'*/
    { 0xb5  ,  0xb4 },   /*'X'*/
    { 0xb5  ,  0x48 },   /*'Y'*/
    { 0xe5  ,  0x9c },   /*'Z'*/
    { 0x69  ,  0x4c },   /*'['*/
    { 0x91  ,  0x24 },   /*'\'*/
    { 0x64  ,  0x2e },   /*']'*/
    { 0x54  ,  0x00 },   /*'^'*/
    { 0x00  ,  0x1c },   /*'_'*/
    { 0x44  ,  0x00 },   /*'`'*/
    { 0x0e  ,  0xae },   /*'a'*/
    { 0x9a  ,  0xba },   /*'b'*/
    { 0x0e  ,  0x8c },   /*'c'*/
    { 0x2e  ,  0xae },   /*'d'*/
    { 0x0e  ,  0xce },   /*'e'*/
    { 0x56  ,  0xd0 },   /*'f'*/
    { 0x55  ,  0x3B },   /*'g'*/
    { 0x93  ,  0xb4 },   /*'h'*/
    { 0x41  ,  0x44 },   /*'i'*/
    { 0x41  ,  0x51 },   /*'j'*/
    { 0x97  ,  0xb4 },   /*'k'*/
    { 0x49  ,  0x44 },   /*'l'*/
    { 0x17  ,  0xb6 },   /*'m'*/
    { 0x1a  ,  0xb6 },   /*'n'*/
    { 0x0a  ,  0xaa },   /*'o'*/
    { 0xd6  ,  0xd3 },   /*'p'*/
    { 0x76  ,  0x67 },   /*'q'*/
    { 0x17  ,  0x90 },   /*'r'*/
    { 0x0f  ,  0x38 },   /*'s'*/
    { 0x9a  ,  0x8c },   /*'t'*/
    { 0x16  ,  0xae },   /*'u'*/
    { 0x16  ,  0xba },   /*'v'*/
    { 0x16  ,  0xf6 },   /*'w'*/
    { 0x15  ,  0xb4 },   /*'x'*/
    { 0xb5  ,  0x2b },   /*'y'*/
    { 0x1c  ,  0x5e },   /*'z'*/
    { 0x6b  ,  0x4c },   /*'{'*/
    { 0x49  ,  0x48 },   /*'|'*/
    { 0xc9  ,  0x5a },   /*'}'*/
    { 0x54  ,  0x00 },   /*'~'*/
    { 0x56  ,  0xe2 },   /*''*/
    { 0xFF  ,  0xFE }    /*''*/
};


void drawChar4x6(spi_t *inst, box_t *box, uint8_t *vram, int16_t x, int16_t y,  char c, DISPLAY_COLOR_VAR colour)
{
    const uint8_t index = ((unsigned char)(c)) - FIRST_CHAR_IDX;

    if (index > 97)
        return;

#ifdef __AVR_MEGA__
    uint8_t data1 = pgm_read_byte(&font4x6[index][0]);
    uint8_t data2 = pgm_read_byte(&font4x6[index][1]);
#else
    uint8_t data1 = font4x6[index][0];
    uint8_t data2 = font4x6[index][1];
#endif
    DISPLAY_COLOR_VAR fg = colour;
#if 0
    DISPLAY_COLOR_VAR bg = !colour;
    if (data2 & 1)	// Descender e.g. j, g
    {
        Platform::DrawPixel(cursorX, y, bg);
        Platform::DrawPixel(cursorX + 1, y, bg);
        Platform::DrawPixel(cursorX + 2, y, bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data1 & 0x80) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x40) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data1 & 0x20) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data1 & 0x10) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x8) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data1 & 0x4) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data1 & 0x2) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x1) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x2) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data2 & 0x80) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data2 & 0x40) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x20) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data2 & 0x10) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data2 & 0x8) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x4) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;
    }
    else
    {
        Platform::DrawPixel(cursorX, y, (data1 & 0x80) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x40) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data1 & 0x20) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data1 & 0x10) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x8) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data1 & 0x4) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data1 & 0x2) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data1 & 0x1) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x2) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data2 & 0x80) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data2 & 0x40) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x20) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, (data2 & 0x10) ? fg : bg);
        Platform::DrawPixel(cursorX + 1, y, (data2 & 0x8) ? fg : bg);
        Platform::DrawPixel(cursorX + 2, y, (data2 & 0x4) ? fg : bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
        y++;

        Platform::DrawPixel(cursorX, y, bg);
        Platform::DrawPixel(cursorX + 1, y, bg);
        Platform::DrawPixel(cursorX + 2, y, bg);
        Platform::DrawPixel(cursorX + 3, y, bg);
    }
#endif
    if (data2 & 1)	// Descender e.g. j, g
    {
        y++;

        if(data1 & 0x80)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x40)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data1 & 0x20)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data1 & 0x10)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x8)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data1 & 0x4)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data1 & 0x2)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x1)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x2)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data2 & 0x80)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data2 & 0x40)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x20)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data2 & 0x10)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data2 & 0x8)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x4)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;
    }
    else
    {
        if (data1 & 0x80)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x40)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data1 & 0x20)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data1 & 0x10)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x8)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data1 & 0x4)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data1 & 0x2)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data1 & 0x1)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x2)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data2 & 0x80)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data2 & 0x40)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x20)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;

        if (data2 & 0x10)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x, y, fg);
        if (data2 & 0x8)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 1, y, fg);
        if (data2 & 0x4)
            DISPLAY_FUNC_DRAW_PIXEL(inst, box, vram,x + 2, y, fg);
        y++;
    }
}

uint8_t getCharHeight4x6() {
    return 6;
}

uint8_t getCharWidth4x6() {
    return 4;
}

int getRowsInBox4x6(box_t *box) {
    int cnt = 1;
    int t = box->y_min + 6;
    for(; t < box->y_max; t += 6)
        cnt++;
    return cnt;
}

int getColsInBox4x6(box_t *box) {
    int cnt = 1;
    int t = box->x_min + 4;
    for(; t < box->x_max; t += 4)
        cnt++;
    return cnt;
}

int drawStringWindowed4x6(gfxString_t *inst, box_t *box, char *string, int16_t x, int16_t y, int16_t cursorPos, bool cursorState) {
    box_t box__;
    if(box) {
        box__.x_min = box->x_min;
        box__.x_max = box->x_max;
        box__.y_min = box->y_min;
        box__.y_max = box->y_max;
    } else {
        box__.x_min = 0;
        box__.x_max = 128;
        box__.y_min = 0;
        box__.y_max = 64;
    }
    char *pcString = string;
    int16_t cX = x;
    int16_t cY = y;
    int16_t cCnt = 0;
    inst->edgeTouch = 0;
    uint16_t cLineCnt = 0;;
    inst->rowCnt = 0;
    do {
        if(cCnt == inst->maxLen && inst->maxLen) {
            return cCnt;
        }
        if(cursorPos == cCnt) {
            if(cX < box__.x_min) {
                inst->edgeTouch |= inst->EDGE_OUTSIDE_LEFT;
            }
            if(cY <= box__.y_min) {
                inst->edgeTouch |= inst->EDGE_OUTSIDE_UP;
            }
            if(cX >= box__.x_max) {
                inst->edgeTouch |= inst->EDGE_OUTSIDE_RIGHT;
            }
            if(cY >= box__.y_max - 6) {
                inst->edgeTouch |= inst->EDGE_OUTSIDE_DOWN;
            }
        }

        char C, c = C = *pcString;
        if(cursorPos == cCnt) {
            if((cursorState) || (cursorState && C == 0))
                C = (uint8_t)(96+32);
        }
        if(!inst->transparent) {
            if(inst->foreColor != inst->inkColor) {
                ssd1306_draw_rectangle(inst->spi, box, inst->vram, cX, cY, getCharWidth4x6(), getCharHeight4x6(), true, inst->foreColor);
            }
            drawChar4x6(inst->spi, box, inst->vram, cX, cY, C, inst->inkColor);
        }
        if (c == 0) {
            return cCnt - 1;
        }
        switch (c) {
        case '\r':
        case '\n':
            if(cY > box__.y_max)
                return cCnt;
            cX = x;
            cY += 6;
            inst->rowCnt++;
            break;
        case 0x09:
            cX = (4 * inst->tabSpaces) + ((cX / (4 * inst->tabSpaces)) * (4 * inst->tabSpaces));
            break;
        default:
            cX += 4;
            if ((cX + 4 > box__.x_max)
                    && inst->wordWrap == true) {
                cY += 6;
                cX = x;
            }
            break;
        }
        cLineCnt++;
        if(cLineCnt > inst->maxLineLen && inst->maxLineLen) {
            cLineCnt = 0;
            cX = x;
            cY += 6;
            inst->rowCnt++;
        }
        pcString++;
        cCnt++;
    } while (1);
}
