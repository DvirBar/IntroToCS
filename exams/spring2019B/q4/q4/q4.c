#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool IsConstructable(int numbers[], int n, int result);
void InitArr(int arr[], int n);
bool TryConstruct(int nums[], int n, int result, int sum, int* used_nums);

int main() {
    int numbers[6] = {8, 8, 3, 1, 2, 14};
    
    printf("%d\n", IsConstructable(numbers, 6, 8));
    
    return 0;
}

bool IsConstructable(int numbers[], int n, int result) {
    int* used_nums = malloc(sizeof(int)*n);
    InitArr(used_nums, n);
    bool success = false;
    
    success = TryConstruct(numbers, n, result, 0, used_nums);
    
    free(used_nums);
    return success;
}

bool TryConstruct(int nums[], int n, int result, int sum, int* used_nums) {
    if(sum == result)
        return true;
    
    bool success = false;
    
    for(int i=0; i<n; i++) {
        for(int j=-1; j<=1; j+=2) {
            if(!used_nums[i]) {
                used_nums[i] = 1;
                success = TryConstruct(nums, n, result, sum+j*nums[i], used_nums);
                
                if(success)
                    return true;
                
                used_nums[i] = 0;
            }
        }
    }
    
    return false;
}


void InitArr(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        arr[i] = 0;
    }
}
