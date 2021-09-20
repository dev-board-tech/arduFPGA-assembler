#ifndef AVRASMCOMPILER_H
#define AVRASMCOMPILER_H

#include <stdint.h>
/*
 * ";"
 * "|"
 * "&"
 * "\"
 * ".device"
 * ".equ"
 * ".def"
 * ".undef"
 * "#pragma"
 * "#define"
 * "defined"
 * "#if"
 * "#ifdef"
 * "#ifndef"
 * "#elif"
 * "#endif"
 * ".csecsize"
 * ".exit"
 * ".macro"
 * ".endmacro"
 * ".endm"
 * ".nolist"
 * ".list"
 * ".warning"
 * ".error"
 * ".message"
 * ".overlap"
 * ".nooverlap"
 * ".set"
 * ".cseg"
 * ".eseg"
 * ".dseg"
 * ".byte"
 * ".db"
 * ".dw"
 * ".dd"
 * ".dq"
 * "LOW"
 * "HIGH"
 * "BYTE1"
 * "BYTE2"
 */

typedef struct {
    char inst[6];
    uint16_t i;
    enum {
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
    }type;
}instItem_t;

typedef struct {
    uint32_t curAddr;
    uint32_t curLine;
    void *fPtr;
}file_t;

typedef struct avrAsmCompiler_s{
    enum {
        SECTION_PGM = 0,
        SECTION_RAM,
        SECTION_EEP
    }curSection;
    struct {
        uint16_t csegPtr;
        uint16_t dsegPtr;
        uint16_t esegPtr;
        uint16_t macroCnt;
    }intern;
    int8_t maxLabelLen;
}avrAsmCompiler_t;

#endif // AVRASMCOMPILER_H
