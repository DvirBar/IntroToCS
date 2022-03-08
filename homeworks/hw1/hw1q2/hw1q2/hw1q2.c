#include <stdio.h>

int main() {
    char letter;

    printf("Enter letter to count:\n");
    scanf("%c", &letter);

    // Check that the input is a letter
    if((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
        // If a lowercase letter was inserted, we also look for the uppercase one, and vice versa
        char equivLetter;
        if(letter >= 'a' && letter <= 'z') {
            equivLetter = (letter - 'a') + 'A';
        } else {
            equivLetter = (letter - 'A') + 'a';
        }

        // The user is prompted to insert a letters sequence until a '#' character is typed
        char typedLetter;
        int counter = 0;
        printf("Enter the char sequence:\n");

        do {
            int scannedValue = scanf("%c", &typedLetter);
            if(scannedValue == EOF) {
                return 0;
            }

            if(typedLetter == letter || typedLetter == equivLetter) {
                counter++;
            }
        } while(typedLetter != '#');

        printf("The letter appeared %d times\n", counter);
    }

    return 0;
}

