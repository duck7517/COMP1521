#include <stdio.h>
#include <string.h>


int is_vowel(int curr);

int main(void) {
	char curr;
	while (scanf("%c", &curr) != EOF) {
	    if (!is_vowel(curr))  {
	        printf("%c", curr);
	    }
	    
	}
	
	return 0;
}


int is_vowel(int curr) {
    if (curr == 'a' ||
        curr == 'e' ||
        curr == 'i' ||
        curr == 'o' ||
        curr == 'u' ||
        curr == 'A' ||
        curr == 'E' ||
        curr == 'I' ||
        curr == 'O' ||
        curr == 'U'
    ) {
        return 1;
    }
    return 0;
}
