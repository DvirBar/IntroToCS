#include <stdio.h>

#define NUM_LETTERS ('z' - 'a' + 1)

int FindMaxSlimSubstring(char* str1, char* str2);
void BuildHistogram(char* str2, int histogram[NUM_LETTERS]);

int main() {
    char str1[] = "curious", str2[] = "coast";
    printf("%d\n", FindMaxSlimSubstring(str1, str2));
}

int FindMaxSlimSubstring(char* str1, char* str2) {
    int histogram[NUM_LETTERS] = {0};
    int index=0, max=0, curSubSize=0;
    
    BuildHistogram(str2, histogram);

    while(str1[index]) {
        if(histogram[str1[index]-'a']) {
            if(curSubSize > max)
                max = curSubSize;
            curSubSize = 0;
        }
        else
            curSubSize++;
        index++;
    }
    
    return max;
}

void BuildHistogram(char* str2, int histogram[NUM_LETTERS]) {
    int index=0;
    
    while(str2[index]) {
        histogram[str2[index]-'a'] = 1;
        index++;
    }
}
