#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool Scramble(char* cubes[], int n, int colors[], char* traget);
bool ScrambleAux(char* cubes[], int n, int colors[], char* target, int used_cubes[],
                 int used_colors[], int index);
void InitArr(int arr[], int n);
bool IsLetterFound(char* word, char letter);

int main() {
    char* cubes[4] = {"ABC", "AEI", "EOU", "LNRST"};
    int colors[4] = {0, 0, 1, 2};
    
    printf("%d\n", Scramble(cubes, 4, colors, "BONE"));
    printf("%d\n", Scramble(cubes, 4, colors, "CAT"));
    printf("%d\n", Scramble(cubes, 4, colors, "BOT"));
    printf("%d\n", Scramble(cubes, 4, colors, "SET"));
    printf("%d\n", Scramble(cubes, 4, colors, "TO"));
    printf("%d\n", Scramble(cubes, 4, colors, ""));
    
    return 0;
}

bool Scramble(char* cubes[], int n, int colors[], char* target) {
    if(!target[0])
        return true;

    int* used_cubes = malloc(sizeof(int)*n);
    int* used_colors = malloc(sizeof(int)*n);
    InitArr(used_cubes, n);
    InitArr(used_cubes, n);
    
    bool success = ScrambleAux(cubes, n, colors, target, used_cubes, used_colors, 0);
    
    free(used_cubes);
    free(used_colors);
    
    return success;
}

bool ScrambleAux(char* cubes[], int n, int colors[], char* target, int used_cubes[],
                 int used_colors[], int index) {
    if(!target[index])
        return true;
    
    bool success = false;
    
    for(int i=0; i<n; i++) {
        if(!used_cubes[i] && !used_colors[colors[i]] &&
           IsLetterFound(cubes[i], target[index])) {
            used_cubes[i] = 1;
            used_colors[colors[i]] = 1;
            
            success = ScrambleAux(cubes, n, colors, target, used_cubes,
                                  used_colors, index+1);
            
            if(success)
                return true;
            
            used_cubes[i] = 0;
            used_cubes[colors[i]] = 0;
        }
    }
    
    return false;
}

void InitArr(int arr[], int n) {
    for(int i=0; i<n; i++) {
        arr[i] = 0;
    }
}

bool IsLetterFound(char* word, char letter) {
    int index = 0;
    
    while(word[index]) {
        if(word[index] == letter)
            return true;
        index++;
    }
    
    return false;
}


