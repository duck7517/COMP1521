// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);


int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    int16_t dec = 0;
    if (bits[0] == '0') {
        // positive numbers
        for (int i = 0; bits[i] != 0; i++) {
            int asInt = bits[i] - '0';
            dec <<= 1;
            dec |= asInt; 
        }
    } else {
        //negative numbers
        for (int i = 0; bits[i] != 0; i++) {
            int asInt = bits[i] - '0';
            dec <<= 1;
            dec |= asInt; 
        }
        if(dec&1) {
            dec = ~ dec;
            dec <<= 1;
            dec += 1;
            dec *= -1;
        } else {
            dec = ~ dec;
            dec += 1;
            dec *= -1;
        }
    }
    
    return dec;
}


