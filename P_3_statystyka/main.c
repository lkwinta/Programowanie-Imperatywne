#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

#define N_MAX 100000   // maksymalna liczba prób
#define TEST 0         // 1 - ulatwia testowanie programu, 0 - dla automatycznej oceny

// Oblicza wartość średniej arytmetycznej oraz wariancji próby losowej
void aver_varian(const double tab[], size_t n, double *arith_average, double *variance) {
    for(int i = 0; i < n; i++){
        *arith_average += tab[i];
    }
    *arith_average /= (double)n;
    for(int i = 0; i < n; i++){
        *variance += (tab[i] - *arith_average)*(tab[i] - *arith_average);
    }
    *variance /= n;
}

// Wypełnia tablicę tab wynikami n prób Bernoulliego
// 1 - sukces; 0 - porażka
void bernoulli_gen(int tab[], size_t n, double probab) {
    for(int i = 0; i < n; i++){
        if(rand()/(double)RAND_MAX < probab)
            tab[i] = 1;
        else{
            tab[i] = 0;
        }
    }
}

// Dyskretny rozkład prawdopodobieństwa zmiennej losowej - sumy oczek dwóch kostek do gry.
// Wartości zmiennej losowej są liczbami naturalnymi należącymi do przedziału [2-12].
// throws_num - liczba rzutów (jeden rzut to rzut dwoma kostkami).
// Funkcja zapisuje obliczony rozkład w początkowych elementach tablicy tab.
void two_dice_probab_distrib(double distrib[], int throws_num) {
    for(int i = 0; i < throws_num; i++){
        distrib[(rand()%6+1 + rand()%6+1) - 2] += 1;
    }
    for(int i = 0; i < 11; i++)
        distrib[i] /= throws_num;
}

// Oblicza i zwraca Dystrybuantę (Cumulative Distribution Function)
void cum_discret_distrib(double distrib[], size_t n) {
    for(int i = 1; i < n; i++){
        distrib[i] += distrib[i - 1];
    }
}

// Histogram - wykres "słupkowy" wartości funkcji zapisanych w tablicy tab o długości n,
// x_start - wartość pierwszej danej (założenie: przyrost zmiennej niezależnej=1),
// y_scale - wartość zmiennej zależnej odpowiadającej szerokości jednego znaku na wykresie,
void print_histogram(const double tab[], size_t n, int x_start, double y_scale, char mark) {
    for(int i = 0; i < n; i++){
        printf("%2i |", i + x_start);
        for(int k = 0; k < round((tab[i]/y_scale)); k++)
            printf("%c", mark);

        printf(" %.3lf", tab[i]);
        printf("\n");
    }
}


// Symuluje problem Monty'ego-Hall'a dla przypadku 3-bramkowego
// Wejście: adres licznika wygranych przy zmianie wyboru,
//          adres licznika wygranych bez zamiany,
//          liczba gier (prób).
// Funkcja oblicza ile razy wygrywającym wyborem byłaby zmiana decyzji
// i ile razy wygrywałaby opcja przeciwna.
// Założenie: Funkcja wywołuje generator rand dokładnie 2 razy.
//            Pierwsze losowanie: nr drzwi, za którymi jest nagroda.
//            Drugie losowanie: nr drzwi w pierwszym wyborze gracza.
void monty_hall(int *p_switch_wins, int *p_nonswitch_wins, int n) {
    for(int i = 0; i < n; i++){
        int prize_doors = rand()%3 + 1;
        int choosen_doors = rand()%3 + 1;

        if(choosen_doors == prize_doors)
            (*p_nonswitch_wins)++;
        else
            (*p_switch_wins)++;
    }
}

// read double vector of size n
void read_vector_dbl(double tab[], size_t n) {
    for (size_t i = 0; i < n; ++i) {
        scanf("%lf", tab + i);
    }
}

// print double vector of size n (with 2 figures after the decimal point)
void print_vector_dbl(const double tab[], size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        printf("%.3f ", tab[i]);
    }
    printf("\n");
}

// print integer vector
void print_vector_int(const int tab[], size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

// get from input stream one character ignoring leading whitespace
char get_char_ignore_w_sp(void) {
    int c;
    do  c = getchar();
    while(isspace(c));
    return c;
}

int main(void) {
    int to_do, seed, number, itab[N_MAX];
    size_t n;
    double dtab[N_MAX], two_dice_tab[11];
    char mark;
    if (TEST) printf("Numer testu [1, 7]: ");
    scanf("%d", &to_do);
    if(to_do > 1) {
        if(TEST) printf("seed = ");
        scanf("%d",&seed);
        srand(seed);        // ustawienie ziarna dla powterzalnosci wynikow
    }

    switch(to_do) {
        case 1: // aver_varian
            if (TEST) printf("aver_varian: Wpisz dlugosc tablicy: ");
            scanf("%d", &n);
            if(n < 1 || n > N_MAX) {
                printf("n < 1 lub n > N_MAX\n");
                break;
            }
            { double arith_aver, varian;
                if (TEST) printf("Wpisz elementy tablicy: ");
                read_vector_dbl(dtab, n);
                aver_varian(dtab, n, &arith_aver, &varian);
                if (TEST) printf("średnia arith_aver = ");
                printf("%.3f ", arith_aver);
                if (TEST) printf(" wariancja = ");
                printf("%.3f\n ", varian);
            }
            break;
        case 2: // bernoulli_gen
            if (TEST) printf("Liczba prób: ");
            scanf("%d", &n);
            if(n < 0 || n > N_MAX) {
                printf("n < 0 lub n>%d\n",N_MAX);
                break;
            }
            { double probab;
                if (TEST) printf("Prawdopodobieństwo sukcesu: ");
                scanf("%lf", &probab);
                if(probab < 0 || probab > 1) {
                    printf("p<0 lub p>1\n");
                    break;
                }
                bernoulli_gen(itab, n, probab);
                print_vector_int(itab, n);
            }
            break;
        case 3:  // probab_distrib i tablica
        case 5:  // probab_distrib i histogram
            if (TEST) printf("Liczba prób: ");
            scanf("%d", &number);
            if(number <= 0 || number > N_MAX) {
                printf("number <= 0 lub number > N_MAX\n");
                break;
            }
            two_dice_probab_distrib(two_dice_tab, number);
            if(to_do==3)  print_vector_dbl(two_dice_tab, 11);
            else {
                if(TEST) printf("Wpisz znak: ");
                mark = get_char_ignore_w_sp();
                print_histogram(two_dice_tab,11,2,0.005,mark);
            }
            break;
        case 4: case 6:  // var_dystryb i hist
            if (TEST) printf("Liczba rzutów dwiema kostkami: ");
            scanf("%d", &number);
            if(number < 0 || number > N_MAX) {
                printf("number <= 0 lub number > N_MAX\n");
                break;
            }
            two_dice_probab_distrib(two_dice_tab, number);
            cum_discret_distrib(two_dice_tab, 11);
            if(to_do==4)  print_vector_dbl(two_dice_tab, 11);
            else {
                if(TEST) printf("Wpisz znak: ");
                mark = get_char_ignore_w_sp();
                print_histogram(two_dice_tab,11,2,0.02,mark);
            }
            break;
        case 7: // monty_hall
            if (TEST) printf("Wpisz liczbę prób: ");
            scanf("%d", &number);
            if(number <= 0) {
                printf("number<=0\n");
                break;
            }
            { int switch_wins, nonswitch_wins;
                monty_hall(&switch_wins, &nonswitch_wins, number);
                if (TEST) printf("W %d grach zwycięstwo dawała zmiana wyboru drzwi ", number);
                printf("%d ", switch_wins);
                if (TEST) printf("razy,\na po pozostawienie wyboru drzwi bez zmiany  ");
                printf("%d ", nonswitch_wins);
                if (TEST) printf("razy.");
            }
            break;
        default:
            printf("Numer testu spoza zakresu [1, 7] %d", to_do);
            break;
    }
    return 0;
}