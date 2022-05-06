#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "player.h"
#include "card.h"

typedef struct _game{
    uint32_t _total_card_cnt; // = 80
    uint8_t _player_cnt;
    player *_player;
    uint8_t _turn;
    card *_discard;
    card *_deck;
    uint32_t _deck_cnt; // if = 0 shuffle from _discard
    
}game;