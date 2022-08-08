#include <stdio.h>

// read two integers and print all the integers which have their bottom 2 bits set.

int main(void) {
    int x, y;

    scanf("%d", &x);
    scanf("%d", &y);
    
    //mask for bottom 2 bits set
    int setMask = 3;
    
    //loop through all numbers between x and y
    for (int i = x + 1; i < y; i++) {
        //print them if the mask shows 2 bits set 
        int test = i & setMask;
        if (test == setMask) {
            printf("%d\n", i);
        } 
    }
    

    return 0;
}
