/*
 * arduFPGA-assembler.c
 *
 * Created: 9/11/2021 12:24:15 PM
 * Author : Morgoth
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "def.h"
#include "delay.h"
#include "driver/uart.h"
#include "driver/spi.h"
#include DISPLAY_DRIVER_FILE
#include "mmc_sd_spi.h"
#include "fat_fs/inc/ff.h"

#include "app/textEditor.h"

box_t box = {0, 128, 0, 64};// For ssd1306 128x64 pixels.

spi_t spi;


mmc_sd_t uSD;
FATFS fatFs __attribute__((section(".edata")));

bool usd_state;

#ifndef SSD1306_USE_NO_BUF
uint8_t vram[1024] __attribute__((section(".edata")));
#else /* SSD1306_USE_NO_BUF */
uint8_t vram[1];
#endif /* SSD1306_USE_NO_BUF */

textEditor_t fileEditor;
char textBuff[16384] __attribute__((section(".edata")));

timer_t rfshTimer;

void service() {
	timer_service();
}

int main(void)
{
	void (*vect_set_service)(uint16_t) = (void *)BOOT_VECTOR_SET_SERVICE_VECT;
	vect_set_service((uint16_t)service);

	spi.spcr = &SPCR;
	spi.spsr = &SPSR;
	spi.spdr = &SPDR;
	spi_init(&spi);
	DISPLAY_FUNC_INIT(&spi, vram);
	uSD.unitNr = 0;
	uSD.fatFs = &fatFs;
	uSD.spi_inst = &spi;
	uSD.initFlg = true;
	mmc_sd_spi_idle(&uSD);

    fileEditor.filePtr = (textEditorPtr)textBuff;
    fileEditor.maxFileLen = sizeof(textBuff);
    fileEditor.box = box;
    fileEditor.gfxString.foreColor = false;
    fileEditor.gfxString.inkColor = true;
    fileEditor.gfxString.spi = &spi;
    fileEditor.gfxString.tabSpaces = 3;
    fileEditor.gfxString.vram = vram;
    fileEditor.gfxString.wordWrap = false;
    fileEditor.gfxString.maxLen = 0;
    fileEditor.gfxString.maxLineLen = 0;
    fileEditor.textEditMode = false;
    textEditor_Init(&fileEditor);
    addFile(&fileEditor, "main.asm");
    addFile(&fileEditor, "draw.asm");
    addFile(&fileEditor, "ssd1306.asm");
    changeFile(&fileEditor, 0);
    changeFile(&fileEditor, 1);
    changeFile(&fileEditor, 2);
    changeFile(&fileEditor, 0);
	
	rfshTimer.value = 100;
	timer_enable(&rfshTimer, true);
	while (1) {
		if(timer_tik(&rfshTimer)) {
			mmc_sd_spi_idle(&uSD);
			if(uSD.fs_mounted != usd_state) {
				usd_state = uSD.fs_mounted;
			}
			textEditor_edit(&fileEditor, 'c');
			textEditor_goLeft(&fileEditor);
			textEditor_goRight(&fileEditor);
			textEditor_goUp(&fileEditor);
			textEditor_goDown(&fileEditor);

			
			textEditor_Idle(&fileEditor);
		}
	}
}

