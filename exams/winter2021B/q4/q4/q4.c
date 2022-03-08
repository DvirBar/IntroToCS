#include <stdio.h>
#include <stdbool.h>

#define N 4

int shortest_path(int dist[N][N], bool red_ones[N], int k);
int try_path(int dist[N][N], bool red_ones[N], int k, int reds_left, int length,
             int visited[N], int cur, int depth);

int main() {
    int dist[][N] = {0, 1, 2, 3,
                     1, 0, 1, 2,
                     3, 1, 0, 1,
                     2, -1, 1, 0};
    bool red_ones[N] = {false, true, true, false};
    int k = 1;
    
    printf("%d\n", shortest_path(dist, red_ones, k));
}

int shortest_path(int dist[N][N], bool red_ones[N], int k) {
    int visited[N] = {0};
    int length = -1, shortest = -1;
    
    for(int i=0; i<N; i++) {
        visited[i]=1;
        length = try_path(dist, red_ones, k, red_ones[i] ? k-1 : k, 0,
                          visited, i, 1);
        visited[i]=0;
        
        if(length != -1 && (shortest == -1 || length < shortest))
            shortest = length;
    }
    
    return shortest;
}

int try_path(int dist[N][N], bool red_ones[N], int k, int reds_left, int length,
             int visited[N], int cur, int depth) {
    if(depth == N)
        return length;
    
    int shortest = -1, cur_length = 0;
    
    for(int i=0; i<N; i++) {
        if(!visited[i] && dist[cur][i] > 0 &&(!red_ones[i] || reds_left > 0)) {
            visited[i] = 1;
            
            cur_length = try_path(dist, red_ones, k, red_ones[i] ? reds_left-1 : k,
                                  length + dist[cur][i], visited, i, depth+1);
            visited[i] = 0;
            
            if(cur_length != -1 && (shortest == -1 || cur_length < shortest)) {
                shortest = cur_length;
            }
        }
    }
    
    return shortest;
}
