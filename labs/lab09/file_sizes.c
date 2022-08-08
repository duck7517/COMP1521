/*
Lab 9 Exercise: Print File Sizes
Written on November 2021 by z5312476
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    long int total = 0;
    int i = 1;
    while (i < argc) {
        long int size;
        //calculate each file size
        struct stat file;
        if (stat(argv[i], &file) != 0) {
            perror(argv[i]);
            exit(1);
        }
        size = file.st_size;
        printf("%s: %ld bytes\n", argv[i], size);
        total += size;
        i++;
    }
    
    printf("Total: %ld bytes\n", total);
    return 0;
}
