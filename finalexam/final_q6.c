#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// print a specified byte from a file
//
// first command line argument specifies a file
// second command line argument specifies a byte location
//
// output is a single line containing only the byte's value
// printed as a unsigned decimal integer (0..255)
// if the location does not exist in the file
// a single line is printed saying: error

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    
    long int offset = atol(argv[2]);
    
    if (offset >= 0) {
        int c;
        int found = fseek(file, offset, SEEK_SET);
        if (found != 0) {
            printf("error\n");
        } else if ((c = fgetc(file)) < 0) {
            printf("error\n");
        } else {
            printf("%d\n", c);
        }
    } else {
        int c;
        int size;
        offset *= -1;
        int found = fseek(file, -1, SEEK_END);
        if (found != 0) {
            printf("error\n");
        } else if ((size = ftell(file)) < offset) {
            printf("error\n");
        } else {
            int i = 1;
            while (i < offset) {
                fseek(file, -1, SEEK_CUR);
                i++;
            }
            c = fgetc(file);
            printf("%d\n", c);
        }
    }
    fclose(file);
    return 0;
}
