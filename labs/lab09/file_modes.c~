/*
Lab 9 Exercise: Print File Modes
Written on November 2021 by z5312476
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
    
    
    int i = 1;
    while (i < argc) {
        struct stat file;
        if (stat(argv[i], &file) != 0) {
            perror(argv[i]);
            exit(1);
        }
        
        
        // file or directory
        mode_t mode = file.st_mode;
        if (S_ISDIR(mode)) { 
            printf("d");
        } else if (S_ISREG(mode)) {
            printf("-");
        }
        
        // print permissions
        char userR = (mode & S_IRUSR) ? 'r' : '-';
        printf("%c", userR);
        char userW = (mode & S_IWUSR) ? 'w' : '-';
        printf("%c", userW);
        char userX = (mode & S_IXUSR) ? 'x' : '-';
        printf("%c", userX);
        char grR = (mode & S_IRGRP) ? 'r' : '-';
        printf("%c", grR);
        char grW = (mode & S_IWGRP) ? 'w' : '-';
        printf("%c", grW);
        char grX = (mode & S_IXGRP) ? 'x' : '-';
        printf("%c", grX);
        char othR = (mode & S_IROTH) ? 'r' : '-';
        printf("%c", othR);
        char othW = (mode & S_IWOTH) ? 'w' : '-';
        printf("%c", othW);
        char othX = (mode & S_IXOTH) ? 'x' : '-';
        printf("%c", othX);
        
        //file name
        printf(" %s\n", argv[i]);
        
        i++;
    }
    
    return 0;
}
