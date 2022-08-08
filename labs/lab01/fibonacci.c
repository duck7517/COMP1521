#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 46

int fibonacci(int i);

int main(void) {
   // int already_computed[SERIES_MAX + 1] = { 0, 1 };
    int i;
    while (scanf("%d", &i) != EOF) {
	//(void) already_computed; // keep the compiler quiet, should be removed

   
        printf("%d\n", fibonacci(i));
    }
    return EXIT_SUCCESS;
}


int fibonacci(int i) {

   if(i == 0) {
      return 0;
   }
	
   if(i == 1) {
      return 1;
   }
   return fibonacci(i-1) + fibonacci(i-2);
}

