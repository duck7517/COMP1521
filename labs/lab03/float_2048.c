// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//


// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t output;
    // extract sign
    output.sign = f >> 31;
    // use loop to create exponent mask
    uint32_t maskE = 1;
    uint32_t temp = f >> 23;
    
    for (int i = 0; i < 7; i++) {
        maskE <<= 1;
        maskE |= 1;
    }
    output.exponent = temp & maskE;
    // use loop to create frac mask
    uint32_t maskF = 1;
    for (int i = 0; i < 22; i++) {
        maskF <<= 1;
        maskF |= 1;
    }
    output.fraction = f & maskF;
    
    return output;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // for return 1, all exponent bits must be 1 and 
    // at least 1 fraction bit must be 1.
    
    int NaN = 0;
    uint32_t mask = 1;
    // check exponent is all 1 bits
    // if any bit is 0, change expOnes to false
    int expOnes = 1;
    uint32_t tempExp = f.exponent;
    for (int i = 0; i < 8 && expOnes != 0; i++) {
        if (!(tempExp & mask)) {
            expOnes = 0;
        }
        tempExp >>= 1;
    }
    
    //check fraction has at least a single 1 bit
    // if any bit is 1, fracOne is 1
    int fracOne = 0;
    uint32_t tempFrac = f.fraction;
    if (tempFrac > 0) {
        fracOne = 1;
    }
    
    if (expOnes == 1 && fracOne == 1) {
        NaN = 1;
    }
    
    return NaN;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // sign must be positive
    // sign == 0 is positive
    int isPosInf = 0;
    
    // must be infinity
    // all bits of exp must be 1
    int expOnes = 1;
    uint32_t tempExp = f.exponent;
    
    for (int i = 0; i < 8 && expOnes != 0; i++) {
        if ((tempExp & (unsigned long)1) == (unsigned long)0) {
            expOnes = 0;
        }
        tempExp >>= 1;
        
    }
    //printf("%lu %d\n", (unsigned long)tempExp, j);
    if (f.fraction == 0 && expOnes == 1 && f.sign == 0) {
        isPosInf = 1;
    }
    
    return isPosInf;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // sign must be negative
    // sign == 1 is negative
    int isNegInf = 0;
    
    // must be infinity
    // all bits of exp must be 1
    int expOnes = 1;
    uint32_t tempExp = f.exponent;
    for (int i = 0; i < 8 && expOnes != 0; i++) {
        if (!(tempExp & 1)) {
            expOnes = 0;
        }
        tempExp >>= 1;
    }
    
    if (f.fraction == 0 && expOnes == 1 && f.sign == 1) {
        isNegInf = 1;
    }
    
    return isNegInf;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    
    int isZero = 0;
    
    if (f.exponent == 0 && f.fraction == 0) {
        isZero = 1;
    }

    return isZero;
}

/////////////////////////////////////////////////////


uint32_t float_2048(uint32_t f) {
    uint32_t output = 0;
    
    float_components_t input = float_bits(f);
    
    // if input is 0, inf or nan, return itself
    if (is_zero(input) || is_nan(input) || 
        is_positive_infinity(input) || is_negative_infinity(input)) {
        output = f;
    } else {
        // sign of float
        output = (input.sign << 31); 
        
        // edge cases where result will exceed float capacity.
        if ((input.exponent + 11) > 0xff) {
            // make float inf
            input.exponent = 0xff << 23;
            input.fraction = 0;
            
            //convert from struct back to uint32_t
            output |= input.exponent;
            output |= input.fraction;
            
        } else {
            // if result will not exceed limit
            input.exponent = (input.exponent + 11) << 23;
            
            //convert from struct back to uint32_t
            output |= input.exponent;
            output |= input.fraction; 
            
        }
    }
    
    return output;
}
