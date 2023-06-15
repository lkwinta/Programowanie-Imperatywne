#include "helper.h"

//funkcja swap - zamienia liczbê a i b
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

//losuje liczbê z przedzia³u <a,b>
int rand_from_interval(int a, int b) {
    return rand()%(b - a + 1)+a;
}

//generuje losow¹ permutacje zbioru {0, 1, 2, ..., n-1}
void rand_permutation(int n, int tab[], int seed) {
    srand(seed);
    for(int i = 0; i < n; i++)
        tab[i] = i;
    for(int i = 0; i < n - 1; i++){
        int k = rand_from_interval(i, n - 1);
        swap(tab + i, tab + k);
    }
}

//inicjuje bufor kart
void cards_buffer_init(cards_buffer* buffer) {
    buffer->length = 0;
    buffer->first_out = 0;

    for(int i = 0; i < NUMBER_OF_CARDS; i++)
        buffer->cards[i] = 0;
}

//dodaj jedn¹ kartê na koniec buforu
double cards_buffer_push(cards_buffer* buffer, int card_code) {
    if(buffer->length == NUMBER_OF_CARDS)
        return INFINITY;

    if(card_code == -1)
        return -1;

    buffer->cards[(buffer->first_out + buffer->length)%NUMBER_OF_CARDS] = card_code;
    buffer->length++;

    return card_code;
}

//weŸ jedn¹ kartê z koñca buforu
int cards_buffer_pop(cards_buffer* buffer) {
    if(buffer->length == 0)
        return -1;

    buffer->first_out = (buffer->first_out + 1)%NUMBER_OF_CARDS;
    buffer->length--;
    return buffer->cards[(buffer->first_out - 1)%NUMBER_OF_CARDS];
}

//zwraca d³ugoœæ danych w buforze
int cards_buffer_state(const cards_buffer* buffer) {
    return buffer->length;
}

//wypisuje bufor
void cards_buffer_print(const cards_buffer* buffer) {
    for(int i = 0; i < buffer->length; i++){
        printf("%i ", buffer->cards[(buffer->first_out + i)%NUMBER_OF_CARDS]);
    }
    printf("\n");
}