/*
Test 8 Question 3: Creating numbers from letters
Written on November 2021 by z5312476
*/


#include <stdio.h>
#include <stdint.h>

uint32_t hash(uint32_t old_hash_value, uint8_t byte, size_t index);

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    int C = fgetc(file);
    size_t i = 0;
    uint8_t c = C;
    uint32_t counter = 0;
    
    while (C != EOF) {
        
        counter = hash(counter, c, i);
        
        C = fgetc(file);
    }
    
    fclose(file);
    
    printf("%u\n", counter);
    
    return 0;
}

// DO NOT CHANGE THIS FUNCTION

uint32_t hash(uint32_t old_hash_value, uint8_t byte, size_t index) {
    return old_hash_value + (byte << (index % 17));
}
