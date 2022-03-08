#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int a[], int na, int b[], int nb, int c[]);
int merge_sort(int a[], int n);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

int merge_sort(int a[], int n) {
    int len;
    int *temp_array, *base;
    
    temp_array = malloc(sizeof(int)*n);
    
    if(temp_array == NULL) {
        return 0;
    }
    
    for(len = 1; len < n; len *= 2) {
        for(base = a; base < a + n; base += 2*len) {
            merge(base, len, base + len, len, temp_array);
            memcpy(a, temp_array, 2*len*sizeof(int));
        }
    }
    
    free(temp_array);
    
    return 1;
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
