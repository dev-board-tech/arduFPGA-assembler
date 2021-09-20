
#include "avr-asm-compiler.h"

#include <string.h>

char line[65];
char lineBack[65];

#ifdef __AVR_MEGA__
const instItem instrNaked[] PROGMEM = {
#else
const instItem_t instrNaked[] = {
#endif
    {"ASR",		0x9405,	instrNaked->INST_RD},
    {"CLR",		0x2400,	instrNaked->INST_RD},
    {"COM",		0x9400,	instrNaked->INST_RD},
    {"DEC",		0x940A,	instrNaked->INST_RD},
    {"INC",		0x9403,	instrNaked->INST_RD},
    {"LSL",		0x0C00,	instrNaked->INST_RD},
    {"LSR",		0x9406,	instrNaked->INST_RD},
    {"NEG",		0x9401,	instrNaked->INST_RD},
    {"POP",		0x900F,	instrNaked->INST_RD},
    {"PUSH",	0x920F,	instrNaked->INST_RD},
    {"ROL",		0x1C00,	instrNaked->INST_RD},
    {"ROR",		0x9407,	instrNaked->INST_RD},
    {"SER",		0xEF0F,	instrNaked->INST_RD},
    {"SWAP",	0x9402,	instrNaked->INST_RD},
    {"TST",		0x2000,	instrNaked->INST_RD},
    {"ADIW",	0x9600,	instrNaked->INST_RDK},
    {"ANDI",	0x7000,	instrNaked->INST_RDK},
    {"CBR",		0x7000,	instrNaked->INST_RDK},
    {"CPI",		0x3000,	instrNaked->INST_RDK},
    {"LDI",		0xEF0F,	instrNaked->INST_RDK},
    {"ORI",		0x6000,	instrNaked->INST_RDK},
    {"SBCI",	0x4000,	instrNaked->INST_RDK},
    {"SBR",		0x6000,	instrNaked->INST_RDK},
    {"SUBI",	0x5000,	instrNaked->INST_RDK},
    {"LDS",		0x9000,	instrNaked->INST_RDKD},
    {"STS",		0x9200,	instrNaked->INST_RDKD},
    {"ADC",		0x1C00,	instrNaked->INST_RDRR},
    {"ADD",		0x0C00,	instrNaked->INST_RDRR},
    {"AND",		0x2000,	instrNaked->INST_RDRR},
    {"CP",		0x1400,	instrNaked->INST_RDRR},
    {"CPC",		0x0400,	instrNaked->INST_RDRR},
    {"CPSE",	0x1000,	instrNaked->INST_RDRR},
    {"EOR",		0x2400,	instrNaked->INST_RDRR},
    {"MOV",		0x2C00,	instrNaked->INST_RDRR},
    {"MUL",		0x9C00,	instrNaked->INST_RDRR},
    {"OR",		0x2800,	instrNaked->INST_RDRR},
    {"SBC",		0x0800,	instrNaked->INST_RDRR},
    {"SUB",		0x1800,	instrNaked->INST_RDRR},
    {"SBIW",	0x9700,	instrNaked->INST_RPK},
    {"BCLR",	0X9488,	instrNaked->INST_BIT},
    {"BSET",	0X9408,	instrNaked->INST_BIT},
    {"CBI",		0X9800,	instrNaked->INST_BIT},
    {"SBI",		0x9A00,	instrNaked->INST_BIT},
    {"BL",		0XF800,	instrNaked->INST_BIT_LD_ST},
    {"BST",		0XFA00,	instrNaked->INST_BIT_LD_ST},
    {"IN",		0xB000,	instrNaked->INST_IO},
    {"OUT",		0XB800,	instrNaked->INST_IO},
    {"LD",		0x0001,	instrNaked->INST_LD_LDD},
    {"LDD",		0x0002,	instrNaked->INST_LD_LDD},
    {"SBIC",	0x9900,	instrNaked->INST_SKIP_IO},
    {"SBIS",	0x9B00,	instrNaked->INST_SKIP_IO},
    {"SBRC",	0xFC00,	instrNaked->INST_SKIP_REG},
    {"SBRS",	0xFE00,	instrNaked->INST_SKIP_REG},
    {"ST",		0x0001,	instrNaked->INST_ST_STD},
    {"STD",		0x0002,	instrNaked->INST_ST_STD},
    {"CLC",		0x9488,	instrNaked->INST_NAKED},
    {"CLH",		0x94D8,	instrNaked->INST_NAKED},
    {"CLI",		0x94F8,	instrNaked->INST_NAKED},
    {"CLN",		0x94A8,	instrNaked->INST_NAKED},
    {"CLS",		0x94C8,	instrNaked->INST_NAKED},
    {"CLT",		0x94E8,	instrNaked->INST_NAKED},
    {"CLV",		0x94B8,	instrNaked->INST_NAKED},
    {"CLZ",		0x9498,	instrNaked->INST_NAKED},
    {"ICALL",	0x9509,	instrNaked->INST_NAKED},
    {"IJMP",	0x9409,	instrNaked->INST_NAKED},
    {"LPM",		0x95C8,	instrNaked->INST_NAKED},
    {"RET",		0x9508,	instrNaked->INST_NAKED},
    {"RETI",	0x9518,	instrNaked->INST_NAKED},
    {"SEC",		0x9408,	instrNaked->INST_NAKED},
    {"SEI",		0x9478,	instrNaked->INST_NAKED},
    {"SEN",		0x9428,	instrNaked->INST_NAKED},
    {"SES",		0x9448,	instrNaked->INST_NAKED},
    {"SET",		0x9468,	instrNaked->INST_NAKED},
    {"SEV",		0x9438,	instrNaked->INST_NAKED},
    {"SEZ",		0x9418,	instrNaked->INST_NAKED},
    {"SHE",		0x9458,	instrNaked->INST_NAKED},
    {"SLEEP",	0x9588,	instrNaked->INST_NAKED},
    {"WDR",		0x95A8,	instrNaked->INST_NAKED},
    {"NOP",		0X0000,	instrNaked->INST_NOP},
    {"",        0xFFFF, instrNaked->INST_NOP},
};

#ifdef __AVR_MEGA__
const instItem instrToLabel[] PROGMEM = {
#else
const instItem_t instrToLabel[] = {
#endif
    {"CALL",	0x940E,	instrNaked->INST_RBRANCH_LARGE},
    {"JMP",		0x940C,	instrNaked->INST_RBRANCH_LARGE},
    {"RCALL",	0xD000,	instrNaked->INST_RBRANCH_MED},
    {"RJMP",	0xC000,	instrNaked->INST_RBRANCH_MED},
    {"BRBC",	0xF000,	instrNaked->INST_RBRANCH_SMALL},
    {"BRBS",	0xF400,	instrNaked->INST_RBRANCH_SMALL},
    {"BRCC",	0xF400,	instrNaked->INST_RBRANCH_SMALL},
    {"BRCS",	0xF000,	instrNaked->INST_RBRANCH_SMALL},
    {"BREQ",	0xF001,	instrNaked->INST_RBRANCH_SMALL},
    {"BRGE",	0xF404,	instrNaked->INST_RBRANCH_SMALL},
    {"BRHC",	0xF405,	instrNaked->INST_RBRANCH_SMALL},
    {"BRHS",	0xF005,	instrNaked->INST_RBRANCH_SMALL},
    {"BRID",	0xF407,	instrNaked->INST_RBRANCH_SMALL},
    {"BRIE",	0xF007,	instrNaked->INST_RBRANCH_SMALL},
    {"BRLO",	0xF000,	instrNaked->INST_RBRANCH_SMALL},
    {"BRLT",	0xF004,	instrNaked->INST_RBRANCH_SMALL},
    {"BRMI",	0xF002,	instrNaked->INST_RBRANCH_SMALL},
    {"BRNE",	0xF401,	instrNaked->INST_RBRANCH_SMALL},
    {"BRPL",	0xF402,	instrNaked->INST_RBRANCH_SMALL},
    {"BRSH",	0xF400,	instrNaked->INST_RBRANCH_SMALL},
    {"BRTC",	0xF406,	instrNaked->INST_RBRANCH_SMALL},
    {"BRTS",	0xF006,	instrNaked->INST_RBRANCH_SMALL},
    {"BRVC",	0xF403,	instrNaked->INST_RBRANCH_SMALL},
    {"BRVS",	0xF003,	instrNaked->INST_RBRANCH_SMALL},
    {"",        0xFFFF, instrNaked->INST_NOP},
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

static bool removeSpacesAndTabs(char *str) {
    char *rS = str;
    char *rD = str;
    for(; *rD != 0; rS++) {
        if(*rS <= ' ' && *rS)
            continue;
        *rD = *rS;
        rD++;
        if(!*rS)
            return true;
    }
    return false;
}
//Output format:
//     4d4:	cf 92       	push	r12
bool avrAsmCompiler_Compile(file_t *destFile, file_t *srcFile, file_t *tmpLabelFile) {
    return true;
}
