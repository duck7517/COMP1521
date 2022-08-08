#include <stdio.h>
#include <string.h>


#define SIZE 1024

int isEven(int length);

int main(void) {
    char currLine[SIZE];
    while (fgets(currLine, SIZE, stdin) != NULL) {
        int length = strlen(currLine);
        int even = isEven(length);
        if (even == 1) {
            fputs(currLine, stdout);
        }
    }
	
	return 0;
}


int isEven(int length) {
    if ((length % 2) == 0) {
        return 1;
    } else {
        return 0;
    }
}
