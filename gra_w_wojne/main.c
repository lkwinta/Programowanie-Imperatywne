#include <stdio.h>
#include "helper.h"

#define true 1
#define false 0

typedef char bool;

typedef enum {
    STANDARD = 0,
    SIMPLIFIED = 1
} VERSION;

int main() {
    int seed;
    VERSION version;
    int max_conflicts;
    scanf("%d", &seed);
    scanf("%d", (int*)&version);
    scanf("%d", &max_conflicts);

    // przygotowanie tablicy kart
    int tab[NUMBER_OF_CARDS] = {0};
    // generowanie losowej permutacji
    rand_permutation(NUMBER_OF_CARDS, tab, seed);

    //deklaracja bufor�w oznaczaj�cych r�k� gracza A i B
    cards_buffer player_a;
    cards_buffer player_b;
    //deklaracja bufor�w reprezentuj�cych karty wyk�adane na st� przez graczy
    cards_buffer temp_player_a;
    cards_buffer temp_player_b;

    //inicjalizacja bufor�w
    cards_buffer_init(&player_a);
    cards_buffer_init(&player_b);
    cards_buffer_init(&temp_player_a);
    cards_buffer_init(&temp_player_b);

    //przydzielenie graczom potasowanych kart
    for(int i = 0; i < NUMBER_OF_CARDS/NUMBER_OF_PLAYERS; i++)
        cards_buffer_push(&player_a, tab[i]);

    for(int i = NUMBER_OF_CARDS/NUMBER_OF_PLAYERS; i < NUMBER_OF_CARDS; i++)
        cards_buffer_push(&player_b, tab[i]);

    int conflicts = 0;
    int winner = -1;
    bool is_war = false;

    while(conflicts < max_conflicts && cards_buffer_state(&player_a) != 0 && cards_buffer_state(&player_b) != 0){
        //wy�o�enie na st� kart przez obu graczy
        double card_A = cards_buffer_push(&temp_player_a, cards_buffer_pop(&player_a));
        double card_B = cards_buffer_push(&temp_player_b, cards_buffer_pop(&player_b));

        //w przypadku gdy toczy si� wojna wyk�adamy dodatkow� kart�
        if(version == STANDARD && is_war == true){
            card_A = cards_buffer_push(&temp_player_a, cards_buffer_pop(&player_a));
            card_B = cards_buffer_push(&temp_player_b, cards_buffer_pop(&player_b));
        }

        //w czasie wojny komu� sko�czy�y si� karty, oznacza to koniec gry - nierozstrzygni�ty konflikt
        if(card_A == -1 || card_B == -1 || card_A == INFINITY || card_B == INFINITY)
            break;

        if ((int)card_A / NUMBER_OF_COLORS > (int)card_B / NUMBER_OF_COLORS){
            //wygra� gracz A, a wi�c bierze swoje karty ze sto�u, a nast�pnie karty gracza B
            while(cards_buffer_state(&temp_player_a) != 0)
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_a));

            while(cards_buffer_state(&temp_player_b) != 0)
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_b));

            if(version == STANDARD)
                is_war = false;
        } else if ((int)card_A / NUMBER_OF_COLORS == (int)card_B / NUMBER_OF_COLORS){
            //remis
            if(version == STANDARD)
                //je�li gramy z woj� to nic nie robimy, ustawiamy tylko flag� m�wi�c�, �e w nast�pnej iteracji jest wojna
                is_war = true;
            else{
                //je�li gramy w wersj� uproszczon� to gracze odk�adaj� w�asne karty na st�
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_a));
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_b));
            }
        } else {
            //wygra� gracz B, a wi�c bierze ze sto�u swoje karty, a nast�pnie karty gracza A
            while(cards_buffer_state(&temp_player_b) != 0)
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_b));
            while(cards_buffer_state(&temp_player_a) != 0)
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_a));

            if(version == STANDARD)
                is_war = false;
        }

        conflicts++;
    }

    //sprawdzamy kto wygra� gr�
    if(cards_buffer_state(&player_a) == 0 && cards_buffer_state(&player_b) == NUMBER_OF_CARDS){
        winner = 1;
    } else if(cards_buffer_state(&player_a) == NUMBER_OF_CARDS && cards_buffer_state(&player_b) == 0) {
        winner = 0;
    }

    //je�li nikt, oznacza to, �e ka�dy gracz zbiera swoje karty ze sto�u
    while(cards_buffer_state(&temp_player_a) != 0)
        cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_a));
    while(cards_buffer_state(&temp_player_b) != 0)
        cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_b));

    //wypisanie wyniku
    if(conflicts == max_conflicts){
        printf("0\n%i\n%i\n", cards_buffer_state(&player_a), cards_buffer_state(&player_b));
    }
    else if(winner == -1){
        printf("1\n%i\n%i\n", cards_buffer_state(&player_a), cards_buffer_state(&player_b));
    } else if (winner == 0){
        printf("2\n%i", conflicts);
    } else {
        printf("3\n");
        cards_buffer_print(&player_b);
    }

    return 0;
}