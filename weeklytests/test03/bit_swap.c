// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>



// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    
    
    // make mask with alternating 1s and 0s to extract every second bit
    uint64_t oddOnes = 1;    
    for (int i = 0; i < 31; i++) {
        oddOnes <<= 2;
        oddOnes |= 1;
    }   
    
    uint64_t oddBits = value & oddOnes;
    oddBits <<= 1;
    
    uint64_t evenOnes = oddOnes << 1;
    
    uint64_t evenBits = value & evenOnes;
    evenBits >>= 1;
    
    uint64_t output = evenBits | oddBits;
    

    return output;
}
