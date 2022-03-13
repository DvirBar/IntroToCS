#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ABC 'z' - 'a' + 1

int CountChars(char* str, int n, int c);
int FindFirstIndex(char* str, int n, int c);
int FindLastIndex(char* str, int n, int c);
bool AreEqual(char* s1, char* s2, int n);

int main() {
    char str[] = "aaabcccccdddddeef";
    int length = (int)strlen(str);
    printf("%d\n", CountChars(str, length, 'e'));
    
    char str2[] = "aaabcccccdddddeef";
    printf("%d\n", AreEqual(str, str2, length));
    
    char str3[] = "bbbbcccccddddkllm";
    printf("%d\n", AreEqual(str, str3, length));
    
    return 0;
}

// Part A
int CountChars(char* str, int n, int c) {
    return FindLastIndex(str, n, c) - FindFirstIndex(str, n, c) + 1;
}

int FindFirstIndex(char* str, int n, int c) {
    if(str[0] == c)
        return 0;
    
    int left = 0, right = n-1, mid = (left+right)/2;
    
    while(left <= right) {
        if(str[mid] >= c) {
            if(str[mid] == c && str[mid-1] != c)
                return mid;
            
            right = mid-1;
        }
    
        else
            left = mid+1;
        
        mid = (left+right)/2;
    }
    
    return -1;
}

int FindLastIndex(char* str, int n, int c) {
    if(str[n-1] == c)
        return n-1;
    
    int left = 0, right = n-1, mid = (left+right)/2;
    
    while(left <= right) {
        if(str[mid] <= c) {
            if(str[mid] == c && str[mid+1] != c)
                return mid;
            left = mid+1;
        }
        else
            right = mid-1;
        
        mid = (left+right)/2;
    }
    
    return -1;
}

// Part B
bool AreEqual(char* s1, char* s2, int n) {
    for(int i=0; i<ABC; i++) {
        if(CountChars(s1, n, i+'a') != CountChars(s2, n, i+'a'))
            return false;
    }
    
    return true;
}
