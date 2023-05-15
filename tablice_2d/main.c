#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {
    return A[row * cols + col];
}

void set(int cols, int row, int col, int *A, int value) {
    A[row * cols + col] = value;
}


void print_mat(int rows, int cols, int *t) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%i ", t[i*cols + j]);
        }
        printf("\n");
    }
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
    for(int i = 0; i < rowsA; i++){
        for(int j = 0; j < colsB; j++){
            int sum = 0;
            for(int k = 0; k < colsA; k++){
                sum += get(colsA, i, k, A) * get(colsB, k, j, B);
            }

            set(rowsA, i, j, AB, sum);
        }
    }
}

void read_mat(int rows, int cols, int *t) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            scanf("%i", &t[i*cols + j]);
        }
    }
}


int read_char_lines(char *array[]) {
}

void write_char_line(char *array[], int n) {
}

void delete_lines(char *array[]) {
}

int read_int_lines_cont(int *ptr_array[]) {
    int elements_counter = 1;
    int lines_counter = 0;
    int buffer_counter = 0;

    char buffer[BUF_SIZE] = {0};

    int* ptr = malloc(sizeof(int));

    while(!feof(stdin)){
        char c = fgetc(stdin);

        ptr_array[lines_counter] = &ptr[elements_counter-1];

        while(c != '\n'){
            if(c == ' '){
                int result = atoi(buffer);
                memset(buffer, 0, BUF_SIZE);

                ptr = realloc(ptr,  (elements_counter)*sizeof(int));

                ptr[elements_counter-1] = result;

                buffer_counter = 0;
                elements_counter++;
            } else {
                buffer[buffer_counter] = c;
                buffer_counter++;
            }

            c = fgetc(stdin);
        }

        int result = atoi(buffer);
        memset(buffer, 0, BUF_SIZE);

        ptr = realloc(ptr,  (elements_counter)*sizeof(int));

        ptr[elements_counter-1] = result;

        buffer_counter = 0;
        elements_counter++;

        lines_counter++;
    }
    return lines_counter;
}

void write_int_line_cont(int *ptr_array[], int n) {
}

typedef struct {
    int *values;
    int len;
    double average;
} line_type;

int read_int_lines(line_type lines_array[]) {
}

void write_int_line(line_type lines_array[], int n) {
}

void delete_int_lines(line_type array[], int line_count) {
}

int cmp (const void *a, const void *b) {
}

void sort_by_average(line_type lines_array[], int line_count) {
}

typedef struct {
    int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
}

int cmp_triplets(const void *t1, const void *t2) {
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
}

void read_vector(int *v, int n) {
}

void write_vector(int *v, int n) {
}

int read_int() {
    char c_buf[BUF_SIZE];
    fgets(c_buf, BUF_SIZE, stdin);
    return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
    int to_do = read_int();

    int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
    int n, lines_counter, rowsA, colsA, rowsB, colsB;
    int rows, cols, n_triplets;
    char *char_lines_array[TAB_SIZE] = { NULL };
    int continuous_array[TAB_SIZE];
    int *ptr_array[TAB_SIZE];
    triplet triplet_array[TAB_SIZE];
    int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
    int x[TAB_SIZE], y[TAB_SIZE];
    line_type int_lines_array[TAB_SIZE];

    switch (to_do) {
        case 1:
            scanf("%d %d", &rowsA, &colsA);
            read_mat(rowsA, colsA, A);
            scanf("%d %d", &rowsB, &colsB);
            read_mat(rowsB, colsB, B);
            prod_mat(rowsA, colsA, colsB, A, B, AB);
            print_mat(rowsA, colsB, AB);
            break;
        case 2:
            n = read_int() - 1; // we count from 1 :)
            ptr_array[0] = continuous_array;
            read_int_lines_cont(ptr_array);
            write_int_line_cont(ptr_array, n);
            break;
        case 3:
            n = read_int() - 1;
            read_char_lines(char_lines_array);
            write_char_line(char_lines_array, n);
            delete_lines(char_lines_array);
            break;
        case 4:
            n = read_int() - 1;
            lines_counter = read_int_lines(int_lines_array);
            sort_by_average(int_lines_array, lines_counter);
            write_int_line(int_lines_array, n);
            delete_int_lines(int_lines_array, lines_counter);
            break;
        case 5:
            scanf("%d %d %d", &rows, &cols, &n_triplets);
            n_triplets = read_sparse(triplet_array, n_triplets);
            read_vector(x, cols);
            make_CSR(triplet_array, n_triplets, rows, V, C, R);
            multiply_by_vector(rows, V, C, R, x, y);
            write_vector(V, n_triplets);
            write_vector(C, n_triplets);
            write_vector(R, rows + 1);
            write_vector(y, rows);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}


