/*
Test 10 Question 3: Test if A Pathname is a Directory
written by z5312476 on 20 November 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int dir;
    
    struct stat file;
    stat(argv[1], &file);   
    
    // file or directory
    mode_t type = file.st_mode;
    if (S_ISDIR(type)) { 
        dir = 1;
    } else {
        dir = 0;
    }
    
    printf("%d\n", dir);
    return 0;
}
