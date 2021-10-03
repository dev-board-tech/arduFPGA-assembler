/*
 * avr_asm_compiler.h
 *
 * Created: 10/3/2021 11:52:02 AM
 *  Author: Morgoth
 */ 


#ifndef AVR_ASM_COMPILER_H_
#define AVR_ASM_COMPILER_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LINE_SIZE   64
#define TEMPORARY_FILENAME  "tmpFile.tmp"
#define SRC_TEMPORARY_FILENAME  "srcTmpFile.tmp"

typedef enum  {
	INST_NOP,
	INST_BIT,
	INST_BIT_LD_ST,
	INST_IO,
	INST_LD_LDD,
	INST_NAKED,
	INST_RBRANCH_LARGE,
	INST_RBRANCH_MED,
	INST_RBRANCH_SMALL,
	INST_RD,
	INST_RDK,
	INST_RDKD,
	INST_RDRR,
	INST_RPK,
	INST_SKIP_IO,
	INST_SKIP_REG,
	INST_ST_STD
}instItem_type_e;

typedef struct instItem_s{
	char inst[6];
	uint16_t i;
	instItem_type_e type;
}instItem_t;

typedef enum {
	DIR_NONE,
	DIR_DOT_EQU,
	DIR_DOT_DEF,
	DIR_DOT_UNDEF,
	DIR_DOT_MACRO,
	DIR_DOT_ENDMACRO,
	DIR_DOT_ENDM,
	DIR_DOT_WARNING,
	DIR_DOT_ERROR,
	DIR_DOT_MESSAGE,
	DIR_DOT_SET,
	DIR_DOT_CSEG,
	DIR_DOT_ESEG,
	DIR_DOT_DSEG,
	DIR_DOT_BYTE,
	DIR_DOT_DB,
	DIR_DOT_DW,
	DIR_DOT_DD,
	DIR_DOT_DQ,
	DIR_HASHTAG_INCLUDE,
	DIR_HASHTAG_DEFINE,
	DIR_HASHTAG_IF,
	DIR_HASHTAG_IFDEF,
	DIR_HASHTAG_IFNDEF,
	DIR_HASHTAG_ELIF,
	DIR_HASHTAG_ENDIF,
	DIR_HASHTAG_PRAGMA,
	DIR_DEFINED
}directiveItem_type_e;

typedef struct {
	char dir[10];
	directiveItem_type_e type;
}directiveItem_t;

typedef struct {
	uint32_t curAddr;
	uint32_t curLine;
	void *fPtr;
}file_t;

typedef enum {
	SECTION_PGM = 0,
	SECTION_RAM,
	SECTION_EEP
}curentSection_e;

typedef struct avrAsmCompiler_s{
	curentSection_e curSection;
	struct {
		uint16_t csegPtr;
		uint16_t dsegPtr;
		uint16_t esegPtr;
		uint16_t macroCnt;
	}intern;
	int8_t maxLabelLen;
}avrAsmCompiler_t;

bool avrAsmCompiler_Compile(void **files);

#endif /* AVR_ASM_COMPILER_H_ */