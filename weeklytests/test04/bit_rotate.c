#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    int n = n_rotations % 16;
    
    uint16_t output = 0;
    
    uint16_t mask = 0;
    
    if (n >= 0) { // positive case
        // mask to capture highest n bits
        
        for (int i = 0; i < n; i++) {
            mask <<= 1;
            mask |= 1;
        }
        
        mask <<= (16 - n);
        mask &= bits;
        mask >>= (16-n);
        
        // shift bits n times
        bits <<= n;
        
    } else if (n < 0) {
        n = -n;
        // mask to capture lowest n bits
        
        for (int i = 0; i < n; i++) {
            mask <<= 1;
            mask |= 1;
        }
        
        mask &= bits;
        mask <<= (16-n);
        
        // shift bits n times
        bits >>= n;
    }
    
    
    
    // combine them
    output = mask | bits;
    
    return output;
}
