/*
Lab 8 Exercise: Print the Bytes of A File
Written on November 2021 by z5312476
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Please enter at least 1 argument.\n");
        return 1;
    }

    FILE *output_stream = fopen(argv[1], "w");
    
    if (output_stream == NULL) {
        perror("File cannot be created.\n");
        return 1;
    }
    
    int i = 2;
    int c;
    
    while (i < argc) {
        c = atoi(argv[i]);
        fputc(c, output_stream);
        i++;
    }
    
    fclose(output_stream);
    
    return 0;
}

