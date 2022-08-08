// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    uint32_t opcode = 0;
    
    opcode = 1;
    opcode <<= 8;
    uint32_t mask = s;
    opcode |= mask;
    opcode <<= 5;
    mask = t;
    opcode |= mask;
    opcode <<= 16;
    uint16_t maskI = i;
    opcode |= maskI;
    
    return opcode;

}
