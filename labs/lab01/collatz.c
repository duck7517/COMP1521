#include <stdio.h>
#include <stdlib.h>

int collatz(int i);

int main(int argc, char **argv) {
    //(void) argc, (void) argv; // keep the compiler quiet, should be removed

	if (argc == 1) {
	    printf("Usage: ./collatz NUMBER\n");
	} else {
    	int num = atoi(argv[1]);
    	printf("%d\n", num);
        collatz(num);
	}
	
	
	
	return EXIT_SUCCESS;
}



int collatz(int number) {
    if(number == 1) {
        return 1;
    } else if(number%2==0) {
        number = number/2;
        printf("%d\n", number);
        return collatz(number);
    } else {
        number = number*3+1;
        printf("%d\n", number);
        return collatz(number);
    } 
    return 0;
}
