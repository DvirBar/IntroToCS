/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define MASCULINE (1)
#define FEMININE (2)

#define MASC_NOUN_END 'o'
#define FEM_NOUN_END 'a'

#define Z_SIBILANT 'z'
#define X_SIBILANT 'x'
#define Y_SIBILANT 'y'
#define GN_SIBILANT "gn"
#define PS_SIBILANT "ps"
#define S_SIBILANT 's'

#define A_VOWEL 'a'
#define O_VOWEL 'o'
#define U_VOWEL 'u'
#define E_VOWEL 'e'
#define I_VOWEL 'i'
#define H_VOWEL 'h'

#define UN (1)
#define UNO (2)
#define UNA (3)
#define UN_APOSTROPHE (4)

#define STARTING_LETTER 0
#define SECOND_LETTER 1

#define UNDEFINED_VALUE -1



int get_gender(char* noun);
bool is_start_sibilant(char* noun);
bool is_vowel(char letter);
bool match_two_letter_comb(char* noun, char* expected);
int get_indefinite_article(char* noun);
char* get_article_value(char* noun);
int get_length_indefinite_article(char* noun);
void add_indefinite_article(char* noun, char* noun_with_article);
void handle_indefinite_article(int max_length);

/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

/**
 * main - reads two integers and calls handle_indefinite_article() accordingly.
 *
 * @returns the status, for the operating system.
 */
int main() {
    int max_length, num_of_nouns;
    scanf("%d %d", &max_length, &num_of_nouns);
    for(int i = 0; i < num_of_nouns; i++) {
        handle_indefinite_article(max_length);
    }
    return 0;
}

// Gets a noun and returns its grammatical gender
int get_gender(char* noun) {
    char ending_letter = noun[strlen(noun)-1];
    
    if(ending_letter == MASC_NOUN_END) {
        return MASCULINE;
    }
    
    if(ending_letter == FEM_NOUN_END) {
        return FEMININE;
    }
    
    return UNDEFINED_VALUE;
}

bool match_two_letter_comb(char* noun, char* expected) {
    return noun[STARTING_LETTER] == expected[STARTING_LETTER] &&
        noun[SECOND_LETTER] == expected[SECOND_LETTER];
}

// Return true if the noun begins with a sibilant letters combination
bool is_start_sibilant(char* noun) {
    char starting_letter = noun[STARTING_LETTER];
    
    // Tests cases that requires only one letter
    if (starting_letter == Z_SIBILANT ||
       starting_letter == Y_SIBILANT ||
       starting_letter == X_SIBILANT) {
        return true;
    }
    
    // Tests cases that require two letter combinations
    if(match_two_letter_comb(noun, PS_SIBILANT) ||
       match_two_letter_comb(noun, GN_SIBILANT)) {
        return true;
    }
    
    if(starting_letter == S_SIBILANT && !is_vowel(noun[SECOND_LETTER])) {
        return true;
    }
    
    return starting_letter == I_VOWEL && is_vowel(noun[SECOND_LETTER]);
}

// Returns true if the letter is a vowel
bool is_vowel(char letter) {
    return letter == I_VOWEL || letter == U_VOWEL ||
           letter == A_VOWEL || letter == E_VOWEL || letter == O_VOWEL;
}

// Returns an index of the provided indefinite article with respect to the provided noun
int get_indefinite_article(char* noun) {
    // First, check the noun's gender
    int gender = get_gender(noun);
    
    if(gender == MASCULINE) {
        if(is_start_sibilant(noun)) {
            return UNO;
        }
        
        return UN;
    }
    
    // Else, the gender is feminine
    if(is_vowel(noun[STARTING_LETTER])) {
        return UN_APOSTROPHE;
    }
    
    return UNA;
}

// Returns the actual indefinite article string for the provided noun
char* get_article_value(char* noun) {
    char* indefinite_articles[] = { "un ", "uno ", "una ", "un'"};
    
    return indefinite_articles[get_indefinite_article(noun)-1];
}

// Returns the length of the noun with its indefinite article
int get_length_indefinite_article(char* noun) {
    char* indefinite_article = get_article_value(noun);
    
    // strlen returns unsigned long, so we explicitly cast it to int
    return (int)(strlen(indefinite_article) + strlen(noun));
}

// Adds an indefinite article to the provided noun
void add_indefinite_article(char* noun, char* noun_with_article) {
    // Add the indefinite article first
    noun_with_article = strcat(noun_with_article, get_article_value(noun));

    strcat(noun_with_article, noun);
}

// Asks the user to insert a noun and prints the noun with its indefinite article
void handle_indefinite_article(int max_length) {
    // Allocate memory for noun input
    char *noun = (char*)malloc(sizeof(char)*max_length+1);
    scanf(" %s", noun);

    // Allocate memory for noun with article and assign it
    int indefinite_article_len = get_length_indefinite_article(noun);

    char *indefinite_noun = (char*)malloc(sizeof(char)*indefinite_article_len+1);
    add_indefinite_article(noun, indefinite_noun);
    
    printf("%s\n", indefinite_noun);

    // Memory cleanup
    free(noun);
    free(indefinite_noun);
}
