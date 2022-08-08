#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    uint32_t decoded = 0;
    int n_hex_digits = 2 * (sizeof packed_bcd_value);
    
    for (int which_digit = n_hex_digits - 1; which_digit >= 0; which_digit--) {
     int bit_shift = 4 * which_digit;
     uint32_t shift_value = packed_bcd_value >> bit_shift;
     
     int hex_digit = shift_value & 0xF;
     decoded = decoded * 10 + hex_digit;
        
    }
  
    return decoded;
}
