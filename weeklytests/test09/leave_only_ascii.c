/*
Test 9 Question 3: Delete non-ASCII characters from a file
Written on November 2021 by z5312476
*/


#include <stdio.h>


int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r+");
    FILE *temp = fopen("copy", "w+");
    
    // copy contents to temp
    int c = fgetc(file);
    while (c != EOF) {
        fputc(c, temp);
        c = fgetc(file);
    }
    fclose(file);
    fclose(temp);
    
   // FILE *file1 = fopen(argv[1], "w");
   // FILE *temp1 = fopen("copy", "r");
    file = fopen(argv[1], "r+");
    temp = fopen("copy", "w+");
    // copy back ASCII
    int d;
    while ((d = fgetc(temp)) != EOF) {
        if (d < 127 && d >= 0) {
            fputc(c, file);
        }
    }
    
    
    fclose(file);
    remove("copy");
    return 0;
}
