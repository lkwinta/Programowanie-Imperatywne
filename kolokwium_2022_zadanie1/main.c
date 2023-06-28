#include <stdio.h>
#include <stdlib.h>

typedef struct _matrix {
    int rows;
    int cols;
    double** data;
} Matrix;

//Tworzy Macierz
int create_matrix(Matrix* pmatrix, int rows, int cols){
    if(rows < 1 || cols < 1)
        return 0;

    pmatrix->rows = rows;
    pmatrix->cols = cols;

    pmatrix->data = malloc(sizeof(double*)*rows);
    for(int i = 0; i < rows; i++){
        pmatrix->data[i] = calloc(cols, sizeof(double));
    }

    return 1;
}

int get(Matrix* pm, int row, int col, double* pvalue){
    if( row < 0 || col < 0 ||
        row >= pm->rows || col >= pm->cols ||
        pvalue == NULL)
            return 0;

    *pvalue = pm->data[row][col];

    return 1;
}

int set(Matrix* pm, int row, int col, double pvalue){
    if( row < 0 || col < 0 ||
        row >= pm->rows || col >= pm->cols)
        return 0;

    pm->data[row][col] = pvalue;

    return 1;
}

void create_identity_matrix(Matrix* pm, int size) {
    if(!create_matrix(pm, size, size))
        return;

    for(int i = 0; i < size; i++){
        if(!set(pm, i, i, 1))
            return;
    }
}

double dot_prod_vect(const double* v1, const double* v2, int size){
    double result = 0;

    for(int i = 0; i < size; i++){
        result += v1[i]*v2[i];
    }

    return result;
}

void mul_vect(double* result, const Matrix* pm, const double* vect){
    //zalozenie, result zaalokowane, jesli nie to
    //result = malloc(sizeof(double)*pm->rows);

    for(int i = 0; i < pm->rows; i++){
        result[i] = dot_prod_vect(pm->data[i], vect, pm->cols);
    }
}

void max_element_in_row(double* maxdata, const Matrix* pm){
    for(int i = 0; i < pm->rows; i++){
        double maxval = pm->data[i][0];

        for(int j = 1; j < pm->cols; j++){
            if(maxval < pm->data[i][j])
                maxval = pm->data[i][j];
        }

        maxdata[i] = maxval;
    }
}

void print_mat(Matrix* pm){
    for(int i = 0; i < pm->rows; i++){
        for(int j = 0; j < pm->cols; j++){
            printf("%f ", pm->data[i][j]);
        }

        printf("\n");
    }
}

int main(void) {
    Matrix m;
    create_identity_matrix(&m, 5);
    print_mat(&m);

    printf("\n");

    set(&m, 0, 1, 5);
    print_mat(&m);

    double a;
    get(&m, 0, 1, &a);
    printf("%f \n", a);


    double v1[] = {1, 2, 3, 4, 5};
    double v2[] = {1, 2, 3, 4, 5};
    double v3[5];
    max_element_in_row(v3, &m);

    printf("%f \n", dot_prod_vect(v1, v2, 5));

    for(int i = 0; i < 5; i++)
        printf("%f ", v3[i]);

    printf("\n");

    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.cols; j++){
            set(&m, i, j, i);
        }
    }

    print_mat(&m);

    mul_vect(v3, &m, v1);
    for(int i = 0; i < 5; i++)
        printf("%f ", v3[i]);

    printf("\n");

    return 0;
}