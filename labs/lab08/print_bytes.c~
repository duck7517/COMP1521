/*
Lab 8 Exercise: Print the Bytes of A File
Written on November 2021 by z5312476
*/

#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    
    char *filename = argv[1];
    
    FILE *file = fopen(filename, "r");
    int c = fgetc(file);
    long int i = 0;
    
    while (c != EOF) {
        if (isprint(c) == 0) {
            printf("byte %4ld: %3d 0x%02x\n", i, c, c);
        } else {
            printf("byte %4ld: %3d 0x%02x '%c'\n", i, c, c, c);
        }
        
        c = fgetc(file);
        i++;
    }
    
    fclose(file);
    return 0;
    
}





