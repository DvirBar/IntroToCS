#include <stdio.h>
#define N 4

int abs_value(int value);
int is_strong(int mat[N][N], int row, int column);
int space_rank(int mat[N][N], int row, int column);
void matrix_input(int mat[N][N]);
int matrix_strong_elems(int mat[N][N]);
int matrix_space_rank(int mat[N][N]);
void print_matrix_properties(int strong_elements, int matrix_space);

int main() {
    int mat[N][N] = {{0}};
    matrix_input(mat);
    int matrix_space = matrix_space_rank(mat);
    int strong_elems = matrix_strong_elems(mat);

    print_matrix_properties(strong_elems, matrix_space);
    return 0;
}

// Returns the absolute value of a number
int abs_value(int value) {
    int isNegative = value < 0;
    return value + isNegative*(-value)*2;
}

/* Returns 1 if a matrix element is greater than all
   of its neighbors, and 0 otherwise */
int is_strong(int mat[N][N], int row, int column) {
    int upper_neighbor = row == 0 ||
            mat[row][column] > mat[row-1][column];
    int bottom_neighbor = row == N-1 ||
            mat[row][column] > mat[row+1][column];
    int left_neighbor = column == 0 ||
            mat[row][column] > mat[row][column-1];
    int right_neighbor = column == N-1 ||
            mat[row][column] > mat[row][column+1];

    return (upper_neighbor + bottom_neighbor
            + left_neighbor + right_neighbor) / 4;
}

// Returns a matrix member's diff from its right neighbor
int space_rank(int mat[N][N], int row, int column) {
    int hasNeighbor = column != N-1;
    int rank = abs_value(mat[row][column]-mat[row][column+hasNeighbor]);

    return rank;
}

// Gets matrix values input from user
void matrix_input(int mat[N][N]) {
    printf("Please enter a matrix:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

// Returns how many strong elements a matrix has
int matrix_strong_elems(int mat[N][N]) {
    int strong_num = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(is_strong(mat, i, j)) {
                strong_num++;
            }
        }
    }

    return strong_num;
}

// Returns the matrix elements' space ranks sum
int matrix_space_rank(int mat[N][N]) {
    int rank_sum = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            rank_sum = rank_sum + space_rank(mat, i, j);
        }
    }

    return rank_sum;
}

/* Prints the sum the elements' space ranks
 * and the number of the strong elements in the matrix */
void print_matrix_properties(int strong_elems, int matrix_space) {
    printf("Strong elements: %d\n", strong_elems);
    printf("Space rank: %d", matrix_space);
}

