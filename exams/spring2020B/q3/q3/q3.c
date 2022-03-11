#include <stdio.h>
#include <stdbool.h>

#define NUM_LETTERS ('z' - 'a' + 1)

int ShortestSubstring(char* str);
//void CreateHistogram(char* str, int histogram[NUM_LETTERS]);
bool Compare(int hist_full[NUM_LETTERS], int hist_substr[NUM_LETTERS]);

int main() {
    char str[] = "aabcaadefacebaa";
    
    printf("%d\n", ShortestSubstring(str));
    return 0;
}

int ShortestSubstring(char* str) {
    char *front = str, *back = str;
    int hist_full[NUM_LETTERS] = {0}, hist_substr[NUM_LETTERS] = {0};
    
    while(*str)
        ++hist_full[*str++ - 'a'];
    
    int shortest = (int)(str - front);
    while(*front) {
        ++hist_substr[*front++ - 'a'];
        
        while(Compare(hist_full, hist_substr)) {
            if(front - back < shortest)
                shortest = (int)(front - back);
            --hist_substr[*back++ - 'a'];
        }
    }
    
    return shortest;
}
              
bool Compare(int hist_full[NUM_LETTERS], int hist_substr[NUM_LETTERS]) {
    for(int i=0; i<NUM_LETTERS; i++) {
        if(hist_full[i] && !hist_substr[i])
            return false;
    }
    
    return true;
}
