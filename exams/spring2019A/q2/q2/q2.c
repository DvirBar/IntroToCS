#include <stdio.h>

#define N1 11
#define N2 9

int FindOddOccuring(int arr[], int n);

int main(int argc, const char * argv[]) {
    int arr1[N1] = {8, 8, 5, 5, 6, 6, -1, -1, 7, 7, 3};
    int arr2[N2] = {1, 1, 5, 5, 1, 1, 5, 1, 1};
    
    printf("%d\n", FindOddOccuring(arr1, N1));
    printf("%d\n", FindOddOccuring(arr2, N2));
    
    return 0;
}

int FindOddOccuring(int arr[], int n) {
    int left = 0, right = n-1, mid = (left+right)/2;
    
    while(left <= right) {
        if(mid > 0 && mid < n-1 && arr[mid] != arr[mid-1] && arr[mid] != arr[mid+1])
            return arr[mid];
        else if(mid == 0 && arr[mid] != arr[mid+1])
            return arr[mid];
        else if(mid == n-1 && arr[mid] != arr[mid-1])
            return arr[mid];

        if(arr[mid] == arr[mid+1]) {
            if(mid%2 == 0)
                left = mid+1;
            else
                right = mid-1;
        }
        
        if(arr[mid] == arr[mid-1]) {
            if(mid%2 == 0)
                right = mid-1;
            else
                left = mid+1;
        }
        
        mid = (left+right)/2;
    }
    
    return -1;
}
