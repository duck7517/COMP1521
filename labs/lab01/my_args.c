#include <stdio.h>

int main(int argc, char **argv) {
	//(void) argc, (void) argv; // keep the compiler quiet, should be removed
    int args = argc - 1;
	printf("Program name: %s \n", argv[0]);
	if (argc == 1) {
	    printf("There are no other arguments\n");
	} else if (argc == 2) {
	    printf("There is 1 argument:\n");
	    printf("\tArgument 1 is \"%s\"", argv[1]);
	} else if (argc > 2) {
	    printf("There are %d arguments:\n", args);
	    int i = 1;
	    while (i <= args) {
	        printf("\tArgument %d is \"%s\" \n", i, argv[i]);
	        i++;
        }
        
	}

	return 0;
}
