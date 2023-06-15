#ifndef GRA_W_WOJNE_HELPER_H
#define GRA_W_WOJNE_HELPER_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_COLORS 4

typedef struct {
    int first_out;
    int length;
    int cards[NUMBER_OF_CARDS];
} cards_buffer;

void rand_permutation(int n, int tab[], int seed);

void cards_buffer_init(cards_buffer* buffer);
double cards_buffer_push(cards_buffer* buffer, int card_code);
int cards_buffer_pop(cards_buffer* buffer);
int cards_buffer_state(const cards_buffer* buffer);
void cards_buffer_print(const cards_buffer* buffer);

#endif //GRA_W_WOJNE_HELPER_H
