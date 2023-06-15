#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE 40

#define TEST 0    // 1 - dla testow,  0 - dla oceny automatycznej

void read_vec(double x[], size_t n) {
    for(size_t i=0; i<n; ++i)  scanf("%lf",x++);
}

void print_vec(const double x[], size_t n) {
    for(size_t i=0; i<n; ++i) printf("%.4f ",x[i]);
    printf("\n");
}

void read_mat(double A[][SIZE], size_t m, size_t n) {
    for(size_t i=0; i<m; ++i) {
        for(size_t j=0; j<n; ++j)  scanf("%lf",&A[i][j]);
    }
}

void print_mat(const double A[][SIZE], size_t m, size_t n) {
    for(size_t i=0; i<m; ++i) {
        for(size_t j=0; j<n; ++j)  printf("%.4f ",A[i][j]);
        printf("\n");
    }
}

void mat_product(const double A[][SIZE], const double B[][SIZE], double AB[][SIZE], size_t m, size_t p, size_t n) {
    for(int wA = 0; wA < m; wA++){
        for(int kB = 0; kB < n; kB++){
            double sum = 0;

            for(int i = 0; i < p; i++){
                sum += A[wA][i] * B[i][kB];
            }

            AB[wA][kB] = sum;
        }
    }
}

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

// 5.2.1 Triangularyzacja, wyznacznik i rozwiazanie Ax=b dla  macierzy kwadratowej.
// Wersja rozszerzona: Wybor wiersza z maksymalna waroscia |elementu glownego|
// Przy wymianie wierszy nalezy zastosowac wetor permutacji indeksow wierszy.
// Jezeli maksymalna wartosc |elementu glownego| < eps, to wyznacznik = 0.
// Zwraca wyznacznik det. Jezeli =0,  to triangularyzacja moze byc niedokonczona.
// Jezeli wyznacznik != 0, i b,x != NULL,
// to w wektorze x umieszcza rozwiazanie ukladu rownan Ax=b.
double gauss(double A[][SIZE], double b[], double x[], size_t n, double eps) {
    int indices[n];
    double det = 1;

    for(int i = 0; i < n; i++) {
        indices[i] = i;
    }

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(fabs(A[indices[i]][i]) < fabs(A[indices[j]][i])){
                swap(&indices[i], &indices[j]);
                det *= -1;
            }
        }

        if(A[indices[i]][i] == 0)
            return 0;

        for(int j = i + 1; j < n; j++){
            double scalar = A[indices[j]][i] / A[indices[i]][i];
            for(int k = i; k < n; k++){
                A[indices[j]][k] -= A[indices[i]][k]*scalar;
            }
            b[indices[j]] -= b[indices[i]]*scalar;
        }
    }


    for(int i = 0; i < n; i++){
        det *= A[indices[i]][i];
    }

    if(det != 0) {
        for (int i = (int) n - 1; i >= 0; i--) {
            double sum = b[indices[i]];
            for (int j = (int) n - 1; j > i; j--) {
                sum -= x[j] * A[indices[i]][j];
            }
            x[i] = sum / A[indices[i]][i];
        }
    }

    return det;
}

// 5.2.2
// Zwraca wyznacznik i w tablicy B macierz odwrotna (jezlei wyznacznik != 0)
// Jezeli maksymalna bezwzgledna wartosc elementu glownego < eps,
// to funkcja zwraca wartosc wyznacznika det = 0.
// Funkcja zmienia wartosci takze w tablicy A.

double matrix_inv(double A[][SIZE], double B[][SIZE], size_t n, double eps) {
    int indices[n];
    double mat_1[SIZE][SIZE] = {0};
    double det = 1;

    for(int i = 0; i < n; i++) {
        indices[i] = i;
    }
    for(int i = 0; i < n; i++){
        mat_1[i][i] = 1;
    }

    //trójkątna górna
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(fabs(A[indices[i]][i]) < fabs(A[indices[j]][i])){
                swap(&indices[i], &indices[j]);
                det *= -1;
            }
        }

        if(A[indices[i]][i] == 0)
            return 0;

        for(int j = i + 1; j < n; j++){
            double scalar = A[indices[j]][i] / A[indices[i]][i];
            for(int k = i; k < n; k++){
                A[indices[j]][k] -= A[indices[i]][k]*scalar;
            }
            for(int k = 0; k < n; k++){
                mat_1[indices[j]][k] -= mat_1[indices[i]][k]*scalar;
            }
        }
    }

    for(int i = 0; i < n; i++){
        det *= A[indices[i]][i];
    }

    //1 na głównej przekątnej
    for(int i = 0; i < n; i++){
        double scalar = A[indices[i]][i];
        for(int j = i; j < n; j++){
            A[indices[i]][j] /= scalar;

        }
        for(int j = 0; j < n; j++){
            mat_1[indices[i]][j] /= scalar;
        }
    }

    for(int i = (int)n - 1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            double scalar = A[indices[j]][i] / A[indices[i]][i];
            for(int k = i; k < n; k++){
                A[indices[j]][k] -= A[indices[i]][k]*scalar;
            }
            for(int k = 0; k < n; k++){
                mat_1[indices[j]][k] -= mat_1[indices[i]][k]*scalar;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            B[i][j] = mat_1[indices[i]][j];
        }
    }

    return det;
}

int main(void) {

    double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    double b[SIZE], x[SIZE], det, eps = 1.e-13;
    int to_do;
    size_t m,n,p,q;
    if(TEST) printf("Wpisz nr zadania ");
    scanf ("%d", &to_do);
    switch (to_do) {
        case 1:
            if(TEST) printf("Wpisz liczbe wierszy i kolumn mac. kwadratowej: ");
            scanf("%d", &n);
            if(TEST) printf("Wpisz macierz A (wierszami): ");
            read_mat(A,n,n);
            if(TEST) printf("Wpisz wektor b: ");
            read_vec(b,n);
            det = gauss(A, b, x, n, eps);
            printf("%.4f\n",det);
            if(det) print_vec(x,n);
            break;
        case 2:
            if(TEST) printf("Wpisz rozmiar macierzy n = ");
            scanf("%d",&n);
            if(TEST) printf("Wpisz elementy macierzy (wierszami): ");
            read_mat(A,n,n);
            det = matrix_inv(A,B,n,eps);
            printf("%.4f\n",det);
            if(det) print_mat(B,n,n);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
    }
    return 0;
}
