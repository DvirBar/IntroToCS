#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 11


bool IsKSplitable(int arr[], int n, int k);
int SumArr(int arr[], int n);
void InitArr(int* used_indexes, int n);
bool TrySplits(int arr[], int n, int size, int sum_left, int* used_indexes, int depth);

int main() {
    int arr[N] = {9, -2, 3, 17, 5, 3, 8, 4, 1, 1, 2};
    
    printf("%d\n", IsKSplitable(arr, N, 4));
    return 0;
}

bool IsKSplitable(int arr[], int n, int k) {
    int sum = SumArr(arr, n);
    
    if((sum/(double)k)-(sum/k) != 0) {
        return false;
    }
    
    int* used_indexes = malloc(sizeof(int)*n);
    
    InitArr(used_indexes, n);
    used_indexes[0] = 1;
    
    bool success = TrySplits(arr, n, sum/k, sum-arr[0], used_indexes, 1);
    free(used_indexes);
    return success;
}

int SumArr(int arr[], int n) {
    int sum = 0;
    
    for(int i=0; i<n; i++) {
        sum+=arr[i];
    }
    
    return sum;
}

void InitArr(int* used_indexes, int n) {
    for(int i=0; i<n; i++) {
        used_indexes[i]=0;
    }
}

bool TrySplits(int arr[], int n, int size, int sum_left, int* used_indexes, int depth) {
    if(depth == n) {
        if(sum_left == 0)
            return  true;
        
        else
            return false;
    }
    
    bool success = false;
    
    for(int i=0; i<n; i++) {
        if(!used_indexes[i] && (sum_left%size==0 || sum_left/size == (sum_left-arr[i])/size)) {
            used_indexes[i]=1;
            success = TrySplits(arr, n, size, sum_left-arr[i], used_indexes, depth+1);
            
            if(success)
                return true;
            
            used_indexes[i]=0;
        }
    }
    
    return false;
}






