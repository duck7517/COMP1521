/*
Test 8 Question 2: Creating text files without vowels
Written on November 2021 by z5312476
*/

#include <stdio.h>
#include <ctype.h>


int isvowel (int c);

int main(int argc, char *argv[]) {
    
    FILE *input_stream = fopen(argv[1], "r");
    FILE *output_stream = fopen(argv[2], "w");
    
    int c;
    while ((c = fgetc(input_stream)) != EOF) {
        if (isvowel(c) == 0) {
            fputc(c, output_stream);
        }
    }
    
    
    fclose(input_stream);
    fclose(output_stream);
    
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
