/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define N 50
#define M 50
#define RECT 4

// ------------------ Rectangle Dimensions ------------------ //

#define RECT_I_TOP_INDEX 0
#define RECT_J_LEFT_INDEX 1
#define RECT_I_BOTTOM_INDEX 2
#define RECT_J_RIGHT_INDEX 3
#define MIDDLE 2

// ---------------------------------------------------------- //


void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[RECT]);
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);
void prepare_rect_dimensions(int rect[RECT], int n, int m, int h, int w, int current_row,
                             int current_col, int* i_top, int* i_bottom, int* j_left, int* j_right);
void print_array(int a[N][M], int n, int m);

int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}


// Populates an integral image array based on the image provided
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            integral_image[i][j] = image[i][j];
            
            // Top neighbor
            if(i > 0) {
                integral_image[i][j] += integral_image[i-1][j];
            }
            
            // Left neighbor
            if(j > 0) {
                integral_image[i][j] += integral_image[i][j-1];
            }
            
            // Top-left neighbor
            if(i > 0 && j > 0) {
                integral_image[i][j] -= integral_image[i-1][j-1];
            }
        }
    }
}

// Returns the requested rectangle sum in the provided integral image
int sum_rect(int integral_image[][M], int rect[RECT]) {
    int i_top = rect [RECT_I_TOP_INDEX], j_left = rect[RECT_J_LEFT_INDEX],
        i_bottom = rect[RECT_I_BOTTOM_INDEX], j_right = rect[RECT_J_RIGHT_INDEX];
    
    // Compute rectangle sum based on the formula
    int sum = integral_image[i_bottom][j_right];
    
    if(i_top > 0) {
        sum -= integral_image[i_top-1][j_right];
    }
    
    if(j_left > 0) {
        sum -= integral_image[i_bottom][j_left-1];
    }
    
    if(i_top > 0 && j_left > 0) {
        sum += integral_image[i_top-1][j_left-1];
    }
    
    return sum;
}

// Populates a sliding average array based on the integral image provided
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]) {
    int rect[RECT] = {0}, sum = 0, i_top = 0, i_bottom = 0, j_left = 0, j_right = 0;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            prepare_rect_dimensions(rect, n, m, h, w, i, j, &i_top, &i_bottom, &j_left, &j_right);
            sum = sum_rect(integral_image, rect);
            
            average[i][j] = round((double) sum / (h*w));
        }
    }
}


// Prepare rect dimensions and verify that frame is within matrix range
void prepare_rect_dimensions(int rect[RECT], int n, int m, int h, int w, int current_row,
                             int current_col, int* i_top, int* i_bottom, int* j_left, int* j_right) {
    // Find the rectangle frame based on the center cell
    *i_top = current_row - h/MIDDLE;
    *j_left = current_col - w/MIDDLE;
    *i_bottom = current_row + h/MIDDLE;
    *j_right = current_col + w/MIDDLE;
    
    
    rect[RECT_I_TOP_INDEX] = *i_top < 0 ? 0 : *i_top;
    rect[RECT_J_LEFT_INDEX] = *j_left < 0 ? 0 : *j_left;
    rect[RECT_I_BOTTOM_INDEX] = *i_bottom > n-1 ? n-1 : *i_bottom;
    rect[RECT_J_RIGHT_INDEX] = *j_right > m-1 ? m-1 : *j_right;
}



