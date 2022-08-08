/*
Test 9 Question 1: Check a File for non_ASCII Bytes
Written on November 2021 by z5312476
*/


#include <stdio.h>



int main(int argc, char *argv[]) {
    int all_ASCII = 1;
    int i = 0;
    
    FILE *file = fopen(argv[1], "r");
    
    int c;
    
    while ((c = fgetc(file)) != EOF && all_ASCII == 1) {
        if (c >= 128 && c <= 255) {
            all_ASCII = 0;
        } else {
            i++;
        }
    }
    
    if (all_ASCII == 1) {
        printf("%s is all ASCII\n", argv[1]);
    } else if (all_ASCII == 0) {
        printf("%s: byte %d is non-ASCII\n", argv[1], i);
    }
    
    return 0;
}
