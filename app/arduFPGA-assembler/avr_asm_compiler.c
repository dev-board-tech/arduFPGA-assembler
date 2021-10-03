/*
 * avr_asm_compiler.c
 *
 * Created: 10/3/2021 11:51:54 AM
 *  Author: Morgoth
 */ 

#include "avr/pgmspace.h"
#include "avr_asm_compiler.h"
#include "app/textEditor.h"

#include <string.h>

char str1[MAX_LINE_SIZE + 1] __attribute__((section(".edata")));
char str2[MAX_LINE_SIZE + 1] __attribute__((section(".edata")));

#ifdef __AVR_MEGA__
const instItem_t instr[] PROGMEM = {
#else
const instItem_t instr[] = {
#endif
	{"ASR",		0x9405,	INST_RD},
	{"CLR",		0x2400,	INST_RD},
	{"COM",		0x9400,	INST_RD},
	{"DEC",		0x940A,	INST_RD},
	{"INC",		0x9403,	INST_RD},
	{"LSL",		0x0C00,	INST_RD},
	{"LSR",		0x9406,	INST_RD},
	{"NEG",		0x9401,	INST_RD},
	{"POP",		0x900F,	INST_RD},
	{"PUSH",	0x920F,	INST_RD},
	{"ROL",		0x1C00,	INST_RD},
	{"ROR",		0x9407,	INST_RD},
	{"SER",		0xEF0F,	INST_RD},
	{"SWAP",	0x9402,	INST_RD},
	{"TST",		0x2000,	INST_RD},
	{"ADIW",	0x9600,	INST_RDK},
	{"ANDI",	0x7000,	INST_RDK},
	{"CBR",		0x7000,	INST_RDK},
	{"CPI",		0x3000,	INST_RDK},
	{"LDI",		0xEF0F,	INST_RDK},
	{"ORI",		0x6000,	INST_RDK},
	{"SBCI",	0x4000,	INST_RDK},
	{"SBR",		0x6000,	INST_RDK},
	{"SUBI",	0x5000,	INST_RDK},
	{"LDS",		0x9000,	INST_RDKD},
	{"STS",		0x9200,	INST_RDKD},
	{"ADC",		0x1C00,	INST_RDRR},
	{"ADD",		0x0C00,	INST_RDRR},
	{"AND",		0x2000,	INST_RDRR},
	{"CP",		0x1400,	INST_RDRR},
	{"CPC",		0x0400,	INST_RDRR},
	{"CPSE",	0x1000,	INST_RDRR},
	{"EOR",		0x2400,	INST_RDRR},
	{"MOV",		0x2C00,	INST_RDRR},
	{"MUL",		0x9C00,	INST_RDRR},
	{"OR",		0x2800,	INST_RDRR},
	{"SBC",		0x0800,	INST_RDRR},
	{"SUB",		0x1800,	INST_RDRR},
	{"SBIW",	0x9700,	INST_RPK},
	{"BCLR",	0X9488,	INST_BIT},
	{"BSET",	0X9408,	INST_BIT},
	{"CBI",		0X9800,	INST_BIT},
	{"SBI",		0x9A00,	INST_BIT},
	{"BL",		0XF800,	INST_BIT_LD_ST},
	{"BST",		0XFA00,	INST_BIT_LD_ST},
	{"IN",		0xB000,	INST_IO},
	{"OUT",		0XB800,	INST_IO},
	{"LD",		0x0001,	INST_LD_LDD},
	{"LDD",		0x0002,	INST_LD_LDD},
	{"SBIC",	0x9900,	INST_SKIP_IO},
	{"SBIS",	0x9B00,	INST_SKIP_IO},
	{"SBRC",	0xFC00,	INST_SKIP_REG},
	{"SBRS",	0xFE00,	INST_SKIP_REG},
	{"ST",		0x0001,	INST_ST_STD},
	{"STD",		0x0002,	INST_ST_STD},
	{"CLC",		0x9488,	INST_NAKED},
	{"CLH",		0x94D8,	INST_NAKED},
	{"CLI",		0x94F8,	INST_NAKED},
	{"CLN",		0x94A8,	INST_NAKED},
	{"CLS",		0x94C8,	INST_NAKED},
	{"CLT",		0x94E8,	INST_NAKED},
	{"CLV",		0x94B8,	INST_NAKED},
	{"CLZ",		0x9498,	INST_NAKED},
	{"ICALL",	0x9509,	INST_NAKED},
	{"IJMP",	0x9409,	INST_NAKED},
	{"LPM",		0x95C8,	INST_NAKED},
	{"RET",		0x9508,	INST_NAKED},
	{"RETI",	0x9518,	INST_NAKED},
	{"SEC",		0x9408,	INST_NAKED},
	{"SEI",		0x9478,	INST_NAKED},
	{"SEN",		0x9428,	INST_NAKED},
	{"SES",		0x9448,	INST_NAKED},
	{"SET",		0x9468,	INST_NAKED},
	{"SEV",		0x9438,	INST_NAKED},
	{"SEZ",		0x9418,	INST_NAKED},
	{"SHE",		0x9458,	INST_NAKED},
	{"SLEEP",	0x9588,	INST_NAKED},
	{"WDR",		0x95A8,	INST_NAKED},
	{"NOP",		0X0000,	INST_NOP},
	{"",        0xFFFF, INST_NOP},
};

#ifdef __AVR_MEGA__
const instItem_t instrToLabel[] PROGMEM = {
#else
const instItem_t instrToLabel[] = {
#endif
	{"CALL",	0x940E,	INST_RBRANCH_LARGE},
	{"JMP",		0x940C,	INST_RBRANCH_LARGE},
	{"RCALL",	0xD000,	INST_RBRANCH_MED},
	{"RJMP",	0xC000,	INST_RBRANCH_MED},
	{"BRBC",	0xF000,	INST_RBRANCH_SMALL},
	{"BRBS",	0xF400,	INST_RBRANCH_SMALL},
	{"BRCC",	0xF400,	INST_RBRANCH_SMALL},
	{"BRCS",	0xF000,	INST_RBRANCH_SMALL},
	{"BREQ",	0xF001,	INST_RBRANCH_SMALL},
	{"BRGE",	0xF404,	INST_RBRANCH_SMALL},
	{"BRHC",	0xF405,	INST_RBRANCH_SMALL},
	{"BRHS",	0xF005,	INST_RBRANCH_SMALL},
	{"BRID",	0xF407,	INST_RBRANCH_SMALL},
	{"BRIE",	0xF007,	INST_RBRANCH_SMALL},
	{"BRLO",	0xF000,	INST_RBRANCH_SMALL},
	{"BRLT",	0xF004,	INST_RBRANCH_SMALL},
	{"BRMI",	0xF002,	INST_RBRANCH_SMALL},
	{"BRNE",	0xF401,	INST_RBRANCH_SMALL},
	{"BRPL",	0xF402,	INST_RBRANCH_SMALL},
	{"BRSH",	0xF400,	INST_RBRANCH_SMALL},
	{"BRTC",	0xF406,	INST_RBRANCH_SMALL},
	{"BRTS",	0xF006,	INST_RBRANCH_SMALL},
	{"BRVC",	0xF403,	INST_RBRANCH_SMALL},
	{"BRVS",	0xF003,	INST_RBRANCH_SMALL},
	{"",        0xFFFF, INST_NOP}
};

#ifdef __AVR_MEGA__
const directiveItem_t directives[] PROGMEM = {
#else
const directiveItem_t directives[] = {
#endif
	{".EQU", DIR_DOT_EQU},
	{".DEF", DIR_DOT_DEF},
	{".UNDEF", DIR_DOT_UNDEF},
	{".MACRO", DIR_DOT_MACRO},
	{".ENDMACRO", DIR_DOT_ENDMACRO},
	{".ENDM", DIR_DOT_ENDM},
	{".WARNING", DIR_DOT_WARNING},
	{".ERROR", DIR_DOT_ERROR},
	{".MESSOGE", DIR_DOT_MESSAGE},
	{".SET", DIR_DOT_SET},
	{".CSEG", DIR_DOT_CSEG},
	{".ESEG", DIR_DOT_ESEG},
	{".DSEG", DIR_DOT_DSEG},
	{".BYTE", DIR_DOT_BYTE},
	{".DB", DIR_DOT_DB},
	{".DW", DIR_DOT_DW},
	{".DD", DIR_DOT_DD},
	{".DQ", DIR_DOT_DQ},
	{"#INCLUDE", DIR_HASHTAG_INCLUDE},
	{"#DEFINE", DIR_HASHTAG_DEFINE},
	{"#IF", DIR_HASHTAG_IF},
	{"#IFDEF", DIR_HASHTAG_IFDEF},
	{"#IFNDEF", DIR_HASHTAG_IFNDEF},
	{"#ELIF", DIR_HASHTAG_ELIF},
	{"#ENDIF", DIR_HASHTAG_ENDIF},
	{"#PRAGMA", DIR_HASHTAG_PRAGMA},
	{"DEFINED", DIR_DEFINED},
	{"", DIR_NONE}
};

static uint8_t read_c(file_t *file, uint32_t addr) {
	return ((uint8_t *)file->fPtr)[addr];
}

static bool write_c(file_t *file, uint32_t addr, uint8_t data) {
	((uint8_t *)file->fPtr)[addr] = data;
}

static bool append_s(file_t *file, uint8_t data, uint16_t len) {

}

static bool get_line(file_t *file) {

}

static void removeSpacesTabsAndComents(char *str) {
	char *rS = str, *rD = str;
	for(; *rD != 0; rS++) {
		if(*rS <= ' ' && *rS)
		continue;
		if(*rS == ';') {
			*rD = '\0';
			return;
		}
		*rD = *rS;
		rD++;
		if(!*rS)
			return;
	}
}

static void removeChar(char *str, char c) {
	char *rS = str, *rD = str;
	for(; *rD != 0; rS++) {
		if(*rS == c && *rS)
		continue;
		*rD = *rS;
		rD++;
		if(!*rS)
		return;
	}
}

static bool checkDuplicateLabels(FIL *fFil) {
	FIL sFil, dFil;
	char tmpS[MAX_LINE_SIZE + 1];
	if(f_open(&dFil, (TCHAR *)TEMPORARY_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE) != FR_OK) {
		*str1 = '\0';
		*str2 = '\0';
		return true;
	}
	f_rewind(fFil);
	f_truncate(&dFil);
	while(1) {// Go through all registered files.
		if(!f_gets(tmpS, sizeof(tmpS), fFil))
		return false;
		removeChar(tmpS, '\n');
		if(f_open(&sFil, (TCHAR *)tmpS, FA_READ) != FR_OK) {
			*str1 = '\0';
			*str2 = '\0';
			f_close(&dFil);
			return true;
		}
		while(1) {
			// Get next line in the file.
			if(!f_gets((TCHAR *)str1, sizeof(str1), &sFil)) {
				f_close(&sFil);
				break;
			}
			// Check if is a label.
			removeSpacesTabsAndComents(str1);
			char *p = str1;
			for(;*p != ':' && *p != '\0';p++);
			if(*p) {
				char *pp = p;
				for(;*pp != '\0';pp++);
				if(p != pp) {// Is a label.
					// Check if the label is already in the temporary file.
					f_rewind(&dFil);
					bool err = false;
					while(f_gets((TCHAR *)str2, sizeof(str2), &dFil)) {
						removeSpacesTabsAndComents(str2);
						if(!strcmp(str1, str2)) {
							// Restore the comment in the line to return the label with file location.
							str2[strlen(str2)] = ';';
							err = true;
							break;
						}
					}
					// Compose the label and the checked file name to return it or to write it in the temporary file.
					int limit = sizeof(str1) - (pp - str1) - 1;
					strncat(str1, ";", limit);
					strncat(str1, tmpS, limit - 1);
					if(err) {
						f_close(&dFil);
						return true; // str1 = label name and current checked file where the label was found as duplicated, str2 = label name and first file where was found as duplicated.
					}
					// Append label to the temporary file.
					UINT bw;
					char t[2];
					*t = '\n';
					f_lseek(&dFil, f_size(&dFil));
					f_write(&dFil, (void *)str1, strlen(str1), &bw);
					f_write(&dFil, t, 1, &bw);
				}
			}
		}
	}
	f_close(&dFil);
	//f_unlink((TCHAR *)TEMPORARY_FILENAME);
	return false;
}

static bool copyFiles(void **files) {
	textEditorFile_t **_files = (textEditorFile_t **)files;
	textEditorFile_t *fS;
	for(; *_files; fS = *_files++) {// Go through all registered files.

	}
}

static directiveItem_type_e identifyDirective(char **line) {
	directiveItem_t *dir = (directiveItem_t *)&directives[0];
	removeSpacesTabsAndComents(*line);
	int cnt = 0;
	while(dir->type) {
		int dirLen = strlen(dir->dir);
		if(!memcmp(dir->dir, *line, dirLen)) {
			*line = *line + dirLen;
			return dir->type;
		}
		cnt++;
		dir = (directiveItem_t *)&directives[cnt];
	}
	return DIR_NONE;
}

//Output format:
//     4d4:	cf 92       	push	r12
bool avrAsmCompiler_Compile(void **files) {
	textEditorFile_t **fls = (textEditorFile_t **)files;
	textEditorFile_t *fS;
	FIL sFil, srcSFil, srcDFil, incFil;
	fS = *fls;
	if(f_open(&srcDFil, (TCHAR *)SRC_TEMPORARY_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE) != FR_OK) { // Destination file of all included files.
		return true;
	}
	if(f_open(&incFil, (TCHAR *)TEMPORARY_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE) != FR_OK) { // Destination file of the name of all included files to avoid duplicates.
		f_close(&srcDFil);
		return true;
	}
	f_truncate(&srcDFil);
	f_truncate(&incFil);
	bool selfScan = false, finIncFiles = false;
	FSIZE_t fPtrBack1 = 0;
	UINT br = 0, bw = 0;
	char t[2] = {'\n', '\n'};
	while(1) {// Go through all manually included files.
		if(!fS) // After it finish to include files from manualy included files, switch to include files from included files.
		selfScan = true;
		if(selfScan) {

			} else if(f_open(&sFil, (TCHAR *)fS->fileName, FA_READ | FA_OPEN_EXISTING) != FR_OK) {
			f_close(&srcDFil);
			f_close(&incFil);
			return true;
		}
		while(1) {
			// Get next line in the file.
			if(selfScan) {
				f_lseek(&srcDFil, fPtrBack1); // Go to last "#include" included directive.
				if(!f_gets((TCHAR *)str1, sizeof(str1), &srcDFil)) { // Read line.
					f_close(&sFil); // close all files except the temporary file where all the code is saved, and included files temporary file for further usage.
					f_close(&srcSFil);
					//f_close(&srcDFil);
					finIncFiles = true;
					break; // We included all files.
				}
				fPtrBack1 = f_tell(&srcDFil); // Backup the pointer where is the next line to read.
				} else if(!f_gets((TCHAR *)str1, sizeof(str1), &sFil)) {
				f_close(&sFil);
				fls++;
				fS = *fls;
				break;
			}
			char *l = str1;
			directiveItem_type_e dr = identifyDirective(&l);
			bool found = false;
			if(dr != DIR_NONE) {
				switch(dr) {
					case DIR_HASHTAG_INCLUDE:
					removeChar(l, '\"');
					f_rewind(&incFil);
					while(f_gets((TCHAR *)str2, sizeof(str2), &incFil)) {
						removeChar(str2, '\n');
						if(!strcmp(l, str2)) {
							f_lseek(&incFil, f_size(&incFil));
							found = true;
							break;
						}
					}
					if(found)
					break;
					if(f_open(&srcSFil, (TCHAR *)l, FA_READ) != FR_OK)
					return true;
					f_lseek(&srcDFil, f_size(&srcDFil)); // We need to append the new included file.
					while(1) {
						f_read(&srcSFil, str2, sizeof(str2), &br);
						if(!br) {
							f_write(&srcDFil, t, 2, &bw);
							f_write(&incFil, l, strlen(l), &bw);
							f_write(&incFil, t, 1, &bw);
							break;
						}
						f_write(&srcDFil, str2, br, &bw);
						if(br != bw)
						return true;
					}
					break;
					default:
					break;
				}
			}
		}
		if(finIncFiles)
		break;
	}
	// All dependencies included, now copy the content of manually included files.
	fls = (textEditorFile_t **)files;
	while(*fls) {// Go through all manually included files.
		fS = *fls;
		fls++;
		f_rewind(&incFil);
		bool found = false;
		while(f_gets((TCHAR *)str2, sizeof(str2), &incFil)) {
			removeChar(str2, '\n');
			if(!strcmp(fS->fileName, str2)) {
				f_lseek(&incFil, f_size(&incFil));
				found = true;
				break;
			}
		}
		if(found)
		continue;
		if(f_open(&sFil, (TCHAR *)fS->fileName, FA_READ | FA_OPEN_EXISTING) != FR_OK) {
			f_close(&srcDFil);
			f_close(&incFil);
			return true;
		}
		f_lseek(&srcDFil, f_size(&srcDFil)); // We need to append the new included file.
		while(1) {
			f_read(&sFil, str2, sizeof(str2), &br);
			if(!br) {
				f_write(&srcDFil, t, 2, &bw);
				f_write(&incFil, fS->fileName, strlen(fS->fileName), &bw);
				f_write(&incFil, t, 1, &bw);
				break;
			}
			f_write(&srcDFil, str2, br, &bw);
			if(br != bw) {
				f_close(&srcDFil);
				f_close(&incFil);
				return true;
			}
		}
	}
	// All files included, begin compilation.
	if(checkDuplicateLabels(&incFil)) {
		f_close(&srcDFil);
		f_close(&incFil);
		return true;
	}
	f_close(&incFil);
	return false;
}
