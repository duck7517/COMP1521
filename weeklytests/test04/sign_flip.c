#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    uint32_t output = f;
    
    // reset sign bit to 0
    output <<= 1;
    output >>= 1;
    
    // create flipped sign mask
    f >>= 31;
    f = ~f;
    f <<= 31;
    
    output |= f;
    
    return output;
    
}
