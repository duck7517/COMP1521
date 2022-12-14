#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	//(void) argc, (void) argv; // keep the compiler quiet, should be removed
	
	if (argc == 1) {
	    printf("Usage: ./arg_stats NUMBER [NUMBER ...]\n");
	} else {
	    
	    int min = atoi(argv[1]);
	    int max = atoi(argv[1]);
	    int sum = 0;
	    int prod = 1;
	    
	    int i = 1;
	    while (i < argc) {
	        int curr = atoi(argv[i]);
	        if (curr < min) {
	            min = curr;
	        }
	        if (curr > max) {
	            max = curr;
	        }
	        sum += curr;
	        prod = prod * curr;
	        i++;
	    }
	    
	    int mean = sum / (argc - 1);
	    
	    printf("MIN:  %d\n", min);
	    printf("MAX:  %d\n", max);
	    printf("SUM:  %d\n", sum);
	    printf("PROD: %d\n", prod);
	    printf("MEAN: %d\n", mean);
	}
	return 0;
}
