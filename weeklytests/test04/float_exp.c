#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {
    uint32_t expOut;
    // create 8 bit mask
    uint32_t mask = 0;
    for (int i = 0; i < 8; i++) {
        mask <<= 1;
        mask |= 1;
    }
    
    // make lowest 8 bits the exponent
    f >>= 23;
    expOut = f & mask;
    return expOut;
}
