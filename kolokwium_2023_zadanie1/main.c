#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _matrix {
    int rows;
    int cols;
    double** val;
    double* storage;
} Matrix;

void create_matrix(Matrix* pmatrix, int rows, int cols){
    pmatrix->storage = calloc(rows*cols, sizeof(double));
    pmatrix->val = malloc(rows*sizeof(double*));

    for(int i = 0; i < rows; i++){
        pmatrix->val[i] = &pmatrix->storage[i*cols];
    }
    pmatrix->rows = rows;
    pmatrix->cols = cols;
}

void apply_to_rows(Matrix* pmatrix, void (*vect_fun)(double*, int)){
    for(int i = 0; i < pmatrix->rows; i++){
        vect_fun(pmatrix->val[i], pmatrix->cols);
    }
}

void inplace_add_scalar(Matrix* pm, double v){
    for(int i = 0; i < pm->rows*pm->cols; i++){
        pm->storage[i] += v;
    }
}

int swap_cols(Matrix* m, int c1, int c2){
    if(c1 < 0 || c1 >= m->cols || c2 < 0 || c2 >= m->cols)
        return 0;

    for(int i = 0; i < m->rows; i++){
        double temp = m->val[i][c1];
        m->val[i][c1] = m->val[i][c2];
        m->val[i][c2] = temp;
    }

    return 1;
}

void max_element_in_rows(double* maxdata, const Matrix* pm){
    for(int i = 0; i < pm->rows; i++){
        double curr_max = pm->val[i][0];
        for(int j = 1; j < pm->cols; j++) {
            if (pm->val[i][j] > curr_max)
                curr_max = pm->val[i][j];
        }

        maxdata[i] = curr_max;
    }
}

void print_row(double* row, size_t n){
    for(size_t i = 0; i < n; i++){
        printf("%f ", row[i]);
    }
    printf("\n");
}

struct Key {
    double key;
    double tol;
};

int compar(const void* a, const void* b){
    struct Key key = *(struct Key*)a;
    double val = ((double*)a)[0];

    if(fabs(key.key - val) < 0.01)
        return 0;
    if(key.key < val)
        return -1;

    return 1;
}

void find_row(Matrix M, double key, double tol){
    struct Key k = {
            .key = key,
            .tol = tol
    };
    double* row = bsearch(&k, M.val, M.rows, sizeof(double*), compar);

    if (row != NULL)
        print_row(row, M.cols);
}

//funkcja pomocnicza do podpunktu b
void mul_10(double* vect, int size){
    for(int i = 0; i < size; i++){
        vect[i] *= 10;
    }
}

int main(void) {

    //przyklad uzycia apply_to_rows (podpunkt b)
    Matrix m;
    create_matrix(&m, 10, 10);

    //operacje na macierzy

    apply_to_rows(&m, mul_10);


    return 0;
}