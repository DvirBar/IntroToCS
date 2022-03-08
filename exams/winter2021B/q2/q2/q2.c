#include <stdio.h>
#include <stdbool.h>

int FindInTelescope(int arr[], int n, int x);
int FindInSorted(int arr[], int x, int left, int right);

int main() {
    int arr[] = {1, 10, 50, 11, 16, 32, 70, 81};
    
    printf("%d\n", FindInTelescope(arr, 8, 10));
}

int FindInTelescope(int arr[], int n, int x) {
    int foundIndex = -1, i = n;
    
    while(foundIndex == -1 && i>1) {
        foundIndex = FindInSorted(arr, x, i/2, i);
        i/=2;
    }
    
    if(foundIndex == -1)
        foundIndex = arr[0] == x ? 0 : -1;
    
    return foundIndex;
}

int FindInSorted(int arr[], int x, int left, int right) {
    bool isAsnd = arr[right-1] > arr[left];
    int mid = (left+right)/2;
    
    while(left <= right) {
        if(arr[mid] == x)
            return mid;
        if(isAsnd) {
            if(arr[mid] > x) {
                right = mid-1;
            } else {
                left = mid+1;
            }
        } else {
            if(arr[mid]>x) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }
        mid = (left+right)/2;
    }
    
    return -1;
}


