//
//  main.c
//  q4
//
//  Created by Dvir Bartov on 12/03/2022.
//

#include <stdio.h>
#include <stdbool.h>

#define N_ALPH 2
#define N 6
#define M 7

int FindLongestPath(char letters[N_ALPH], char matrix[N][M]);
int TryPaths(char letters[N_ALPH], char matrix[N][M], int visited[N][M],
             int i, int j);
int TrySingleSide(char letters[N_ALPH], char matrix[N][M], int visited[N][M],
                  int i, int j);
bool InLetters(char letter, char letters[N_ALPH]);

int main() {
    char letters[N_ALPH] = {'a', 'b'};
    char matrix[N][M] = {'b', 'b', 'c', 'f', 'e', 'a', 'a',
                         'b', 'c', 'a', 'a', 'c', 'f', 'b',
                         'f', 'e', 'a', 'e', 'b', 'c', 'b',
                         'e', 'f', 'b', 'b', 'c', 'd', 'b',
                         'd', 'a', 'a', 'a', 'e', 'c', 'a',
                         'c', 'd', 'e', 'f', 'f', 'a', 'b'};
    
    printf("%d\n", FindLongestPath(letters, matrix));
    
    return 0;
}

int FindLongestPath(char letters[N_ALPH], char matrix[N][M]) {
    int visited[N][M] = {0};
    int longest = 0, sum = 0;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(!visited[i][j] && InLetters(matrix[i][j], letters)) {
                visited[i][j] = 1;
                sum = TryPaths(letters, matrix, visited, i, j);
                if(sum > longest)
                    longest = sum;
                
            }
        }
    }
    
    return longest;
}

int TryPaths(char letters[N_ALPH], char matrix[N][M], int visited[N][M],
             int i, int j) {
    int sum = 1;
    sum += TrySingleSide(letters, matrix, visited, i+1, j);
    sum += TrySingleSide(letters, matrix, visited, i-1, j);
    sum += TrySingleSide(letters, matrix, visited, i, j+1);
    sum += TrySingleSide(letters, matrix, visited, i, j-1);

    return sum;
}

int TrySingleSide(char letters[N_ALPH], char matrix[N][M], int visited[N][M],
                  int i, int j) {
    if(!visited[i][j]) {
        visited[i][j] = 1;
        if(InLetters(matrix[i][j], letters) && i >= 0 && i <= N && j >= 0 &&
           j <= M)
            return TryPaths(letters, matrix, visited, i, j);
    }
    
    return 0;
}

bool InLetters(char letter, char letters[N_ALPH]) {
    for(int i = 0; i < N_ALPH; i++) {
        if(letter == letters[i])
            return true;
    }
    
    return false;
}
