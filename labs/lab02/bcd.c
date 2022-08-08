#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    
    int tens = bcd_value/10;
    int units = bcd_value % 10;
    
    
    char *bits[17]
    
    //decValue initialised as 00000000 00000000
    int16_t decValue = 0;
    int16_t binTens = 0;
    int16_t binUnits = 0;
    
    //convert integer to binary equivalent
    int j = 1;
    for (int i = 1 << (N_BITS - 1); i > 0; i >>= 1) {
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
    
    //bitwise or with decValue 
    decValue |= binTens;
    
    //left shift 
    decValue << 8;
    
    //bitwise or decValue with binary units
    decValue |= binUnits;
    
    //decValue will now equals to the final binary. convert to dec.
    for (int i = 0; bits[i] != 0; i++) {
        dec <<= 1;
        dec |= asInt; 
    }
    
    
    printf("%d\n%d\n", tens, units);

    return ;
}

