#include <stdio.h>
#include <stdlib.h>

#define N 12

int LongestSequence(int a[], int n, int k);
void InitArr(int a[], int n);
int PopulateHist(int* ones_hist, int a[], int n);

int main() {
    int arr[N] = {1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0};
    
    printf("%d\n", LongestSequence(arr, N, 0));
    
    return 0;
}

int LongestSequence(int a[], int n, int k) {
    int* ones_hist = malloc(sizeof(int)*n);
    InitArr(ones_hist, n);
    int length = PopulateHist(ones_hist, a, n);
    int max = 0, k_left = k+1 >= length ? length-1 : k+1, sum = 0;
    
    for(int i=0; i<length; i++) {
        if(k_left == 0) {
            if(i+1 != length)
                sum += ones_hist[i] - ones_hist[i-(k+1)];
            
            if(sum+k > max)
                max = sum+k;
        }
        
        else {
            sum += ones_hist[i];
            k_left--;
        }
    }
    
    free(ones_hist);
    return max;
}

void InitArr(int a[], int n) {
    for(int i=0; i<n; i++) {
        a[i] = 0;
    }
}

int PopulateHist(int* ones_hist, int a[], int n) {
    int ones_index = 0;
    
    for(int i=0; i<n; i++) {
        if(a[i] == 0)
            ones_index++;
        
        else
            ones_hist[ones_index]++;
    }
    
    return ones_index;
}
