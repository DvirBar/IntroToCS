#include <stdio.h>

#define SPACE ' '

void reverse_words(char* str);
int get_length(char* str);
void reverse_str(char* str, int start, int end);

int main() {
    char str1[] = "geeks quiz practice code";
    char str2[] = " getting good at    coding needs a lot of practice";
    
    reverse_words(str1);
    reverse_words(str2);

    printf("%s\n", str1);
    printf("%s\n", str2);
}

void reverse_words(char* str) {
    int length = get_length(str);
    reverse_str(str, 0, length);
    int word_start = 0;
    for(int i=0; i<=length; i++) {
        if(str[i] == SPACE || !str[i]) {
            if(i == word_start && str[i])
                word_start++;
            else {
                reverse_str(str, word_start, i);
                word_start = i+1;
            }
        }
    }
  
}

int get_length(char* str) {
    int counter = 0;
    
    while(str[counter]) {
        counter++;
    }
    
    return counter;
}

void reverse_str(char* str, int start, int end) {
    char temp = 0;
    
    for(int i=start; i<(end+start)/2; i++) {
        temp = str[i];
        str[i] = str[(end+start)-i-1];
        str[(end+start)-i-1] = temp;
    }
    
    DEBUG;
}
