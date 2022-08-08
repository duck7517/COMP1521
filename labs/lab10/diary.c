/*
Lab 10: Append to a Diary File
Written on November 2021 by z5312476
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    
    char *home = getenv("HOME");
    char *diary = ".diary";
    int l = strlen(home) + strlen(diary) + 2;
    char name[l];
    snprintf(name, l, "%s/%s", home, diary);
    FILE *file = fopen(name, "a");
    
    
    int i = 1;
    
    while (i < argc) {
        fprintf(file, "%s ", argv[i]);
        i++;
    }
    
    
    fprintf(file, "\n");
    
    return 0;
}
