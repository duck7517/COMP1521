// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    uint16_t output = 0;
    uint16_t temp = value;
    
    // shift value so that the msbs are 0s 
    value >>= 8;
    
    
    // shift temp so that lsb are 0s
    temp <<= 8;
    
    // overlay them
    output |= value;
    output |= temp;
    
    return output;
}
