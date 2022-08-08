/*
Test 8 Question 1: Count the vowels in a text file
Written on November 2021 by z5312476
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isvowel (int c);

int main (int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    
    int counter = 0;
    int c = fgetc(file);
    
    while (c != EOF) {
        if (isvowel(c) == 1) {
            counter++;
        }
        
        c = fgetc(file);
    }

    fclose(file);
    
    printf("%d\n", counter);
    
    return 0;
}

int isvowel (int c) {
    int vowel = 0;
    if (c == 'a' || c == 'A' ||
        c == 'e' || c == 'E' ||
        c == 'i' || c == 'I' ||
        c == 'o' || c == 'O' ||
        c == 'u' || c == 'U') 
    {
        
        vowel = 1;
    }
    
    return vowel;
}
