//
//  main.c
//  merge_recursive
//
//  Created by Dvir Bartov on 15/02/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int a[], int na, int b[], int nb, int c[]);
void internal_msort(int a[], int n, int helper_array[]);
void merge_sort(int a[], int n);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

void merge_sort(int a[], int n) {
    int *helper_array = malloc(sizeof(int)*n);
    
    if(helper_array == NULL) {
        return;
    }
    
    internal_msort(a, n, helper_array);
    free(helper_array);
}

void internal_msort(int a[], int n, int helper_array[]) {
    int left = n/2, right = n - left;
    
    if(n < 2)
        return;
    
    internal_msort(a, left, helper_array);
    internal_msort(a + left, right, helper_array);
    
    merge(a, left, a+left, right, helper_array);
    memcpy(a, helper_array, n*sizeof(int));
}

void merge(int a[], int na, int b[], int nb, int c[]) {
    int ia, ib, ic;
    
    for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++) {
        if(a[ia] < b[ib]) {
            c[ic] = a[ia];
            ia++;
        } else {
            c[ic] = b[ib];
            ib++;
        }
    }
    
    for(;ia < na; ia++, ic++) c[ic] = a[ia];
    for(;ib < nb; ib++, ic++) c[ic] = b[ib];
}
