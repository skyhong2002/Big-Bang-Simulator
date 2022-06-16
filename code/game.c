#include "game.h"
#include <math.h>
#include <stdlib.h>

void gameInit(game *bang){
    deckInit(bang);
    bang->_total_card_cnt = 80; // = 80
    bang->_total_player_cnt; 
    bang->_alive_player_cnt;
    bang->_turn = 0;
    // bang->_discard[i];
    bang->_discard_cnt;
    // bang->_deck[i];
    bang->_deck_cnt; // if = 0 shuffle from _discard

    for(int i = 0; i < bang->_total_player_cnt; ++i){
        // playerInit(&bang->_player[i]);
    }
}
int32_t gameEnd(game *bang);
void shuffle(game *bang){
    return;
}
void displayPlayer(const player *player);
void displayHandCard(const player *player){
    return;
}
void displayAction(const player *player, card *c);
card *judge(card **deck); //判定