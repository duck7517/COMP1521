/*
Lab 8 Exercise: Create a File of include
Written on November 2021 by z5312476
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    FILE *output_stream = fopen(argv[1], "w");
    
    int min = atoi(argv[2]);    
    int max = atoi(argv[3]);
    
    int curr = min;
    
    while (curr <= max) {
        fprintf(output_stream, "%d\n", curr);
        curr++;
    }
    
    fclose(output_stream);
    
    return 0;
}
