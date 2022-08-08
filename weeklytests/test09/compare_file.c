/*
Test 9 Question 2: Compare the bytes of Two Files
Written on November 2021 by z5312476
*/


#include <stdio.h>



int main(int argc, char *argv[]) {
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "r");
    
    int c1 = fgetc(file1);
    int c2 = fgetc(file2);
    int same = 1;
    int i = 0;
    
    while (c1 != EOF && c2 != EOF && same == 1) {
        if (c1 != c2) {
            same = 0;
        } else {
            c1 = fgetc(file1);
            c2 = fgetc(file2);
            i++;
        }
    }
    
    if (c1 == EOF && c2 != EOF) {
        printf("EOF on %s\n", argv[1]);
    } else if (c2 == EOF && c1 != EOF) {
        printf("EOF on %s\n", argv[2]);
    } else if (same == 1) {
        printf("Files are identical\n");
    } else if (same == 0) {
        printf("Files differ at byte %d\n", i);   
    }
    
    return 0;
}
