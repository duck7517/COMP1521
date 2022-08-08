// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {

    char *bits = malloc(17*sizeof('\0'));
    bits[N_BITS] = '\0';
    
    if (value < 0) {
        value *= -1;
        value -= 1;
        bits[0] = '1';
        int j = 1;
        for (int i = 1 << (N_BITS - 2); i > 0; i >>= 1) {
            int bin;
            if(value >= i) {
                bin = '0';
                value -= i;
            } else {
                bin = '1';
            }
            bits[j] = bin;
            j++;
        }
        
        
    } else {
        bits[0] = '0';
        int j = 1;
        for (int i = 1 << (N_BITS - 2); i > 0; i >>= 1) {
            int bin;
            if (value >= i) {
                bin = '1';
                value -= i;
            } else {
                bin = '0';
            }
            bits[j] = bin;
            j++;
        }
    }
    
    return bits;
}

