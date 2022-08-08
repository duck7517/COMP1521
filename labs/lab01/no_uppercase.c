#include <stdio.h>
#include <ctype.h>

int main(void) {
    // Take string from stdin until EOF 
    int character = getchar();
    while (character != EOF) {
        int curr;
        if (isupper(character) != 0) {
            // checks that isupper is true, therefore must convert to lower
            curr = tolower(character);
        } else {
            curr = character;
        }
        putchar(curr);
        
        character = getchar();
    }    

	return 0;
}
