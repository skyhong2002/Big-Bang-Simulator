#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "player.h"
#include "card.h"

typedef struct _game
{
    uint32_t _total_card_cnt; // = 80
    uint8_t _total_player_cnt;
    uint8_t _alive_player_cnt;
    player *_player;
    uint8_t _turn;
    card **_discard;
    uint32_t _discard_cnt;
    card **_deck;
    uint32_t _deck_cnt; // if = 0 shuffle from _discard

} game;

void gameInit(game *bang);
int32_t gameEnd(game *bang);
void shuffle(card *discard);
void displayPlayer(const player *player);
void displayHandCard(const player *player);
void displayAction(const player *player, card *c);
card *judge(card **deck); //判定

#endif