#include <stdio.h>
#include <stdbool.h>

#define ABC ('z' - 'a' + 1)
#define SPACE ' '

bool AreAnagrams(char* s1, char* s2);
void PopulateHist(char* str, int hist[ABC]);
char ToLowercase(char letter);

int main(int argc, const char * argv[]) {
    char s1[] = "Tom Marvolo Riddle";
    char s2[] = "I am Lord Voldemort";
    
    printf("%d\n", AreAnagrams(s1, s2));
    
    return 0;
}

bool AreAnagrams(char* s1, char* s2) {
    int hist1[ABC] = {0};
    int hist2[ABC] = {0};
    
    PopulateHist(s1, hist1);
    PopulateHist(s2, hist2);
    
    for(int i=0; i<ABC; i++) {
        if(hist1[i] != hist2[i])
            return false;
    }
    
    return true;
}

void PopulateHist(char* str, int hist[ABC]) {
    while(*str) {
        if(*str != SPACE)
            hist[ToLowercase(*str) - 'a']++;
        str++;
    }
}

char ToLowercase(char letter) {
    if(letter >= 'a')
        return letter;
    
    return letter-'A'+'a';
}


