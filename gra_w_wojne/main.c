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

    //deklaracja buforów oznaczaj¹cych rêkê gracza A i B
    cards_buffer player_a;
    cards_buffer player_b;
    //deklaracja buforów reprezentuj¹cych karty wyk³adane na stó³ przez graczy
    cards_buffer temp_player_a;
    cards_buffer temp_player_b;

    //inicjalizacja buforów
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
        //wy³o¿enie na stó³ kart przez obu graczy
        double card_A = cards_buffer_push(&temp_player_a, cards_buffer_pop(&player_a));
        double card_B = cards_buffer_push(&temp_player_b, cards_buffer_pop(&player_b));

        //w przypadku gdy toczy siê wojna wyk³adamy dodatkow¹ kartê
        if(version == STANDARD && is_war == true){
            card_A = cards_buffer_push(&temp_player_a, cards_buffer_pop(&player_a));
            card_B = cards_buffer_push(&temp_player_b, cards_buffer_pop(&player_b));
        }

        //w czasie wojny komuœ skoñczy³y siê karty, oznacza to koniec gry - nierozstrzygniêty konflikt
        if(card_A == -1 || card_B == -1 || card_A == INFINITY || card_B == INFINITY)
            break;

        if ((int)card_A / NUMBER_OF_COLORS > (int)card_B / NUMBER_OF_COLORS){
            //wygra³ gracz A, a wiêc bierze swoje karty ze sto³u, a nastêpnie karty gracza B
            while(cards_buffer_state(&temp_player_a) != 0)
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_a));

            while(cards_buffer_state(&temp_player_b) != 0)
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_b));

            if(version == STANDARD)
                is_war = false;
        } else if ((int)card_A / NUMBER_OF_COLORS == (int)card_B / NUMBER_OF_COLORS){
            //remis
            if(version == STANDARD)
                //jeœli gramy z woj¹ to nic nie robimy, ustawiamy tylko flagê mówi¹c¹, ¿e w nastêpnej iteracji jest wojna
                is_war = true;
            else{
                //jeœli gramy w wersjê uproszczon¹ to gracze odk³adaj¹ w³asne karty na stó³
                cards_buffer_push(&player_a, cards_buffer_pop(&temp_player_a));
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_b));
            }
        } else {
            //wygra³ gracz B, a wiêc bierze ze sto³u swoje karty, a nastêpnie karty gracza A
            while(cards_buffer_state(&temp_player_b) != 0)
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_b));
            while(cards_buffer_state(&temp_player_a) != 0)
                cards_buffer_push(&player_b, cards_buffer_pop(&temp_player_a));

            if(version == STANDARD)
                is_war = false;
        }

        conflicts++;
    }

    //sprawdzamy kto wygra³ grê
    if(cards_buffer_state(&player_a) == 0 && cards_buffer_state(&player_b) == NUMBER_OF_CARDS){
        winner = 1;
    } else if(cards_buffer_state(&player_a) == NUMBER_OF_CARDS && cards_buffer_state(&player_b) == 0) {
        winner = 0;
    }

    //jeœli nikt, oznacza to, ¿e ka¿dy gracz zbiera swoje karty ze sto³u
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