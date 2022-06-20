#pragma once

#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define GRN "\x1B[32m"
#define MAG "\x1B[35m"
#define RESET "\x1B[0m"

#define MAX_CARD_CNT 80

typedef struct _card
{
    uint8_t _suit; // 1 spade 2 heart 3 diamond 4 club
    uint8_t _number;
    const char *_name;
    const char *_skill;
} card;

typedef struct _role
{
    const char *_name;  //名稱
    const char *_skill; //功能
    uint8_t _lvalue;    //生命值
} role;

typedef struct _player
{
    uint8_t _id;
    char *_name;
    uint8_t _position; // 角色位置
    role *_role;
    char *_identity; // Sceriffo, Vice, Fuorilecce, Rinnegato
    int8_t _max_hp;  // after checking the role is Sceriffo or not
    int8_t _hp;
    int8_t _hand_cnt; // must not higher than _hp at the end of round
    card **_hand;
    card *_gun;   // 0, 1, 2, 3, 4, 5
    card *_horse; // -1, 0, 1
    card *_jail;
    card *_dinamite;
    card *_barrel;
} player;

typedef struct _game
{
    uint32_t _total_card_cnt; // = 80
    int8_t _total_player_cnt;
    int8_t _alive_player_cnt;
    player **_player;
    uint8_t _turn;
    card **_discard;
    int32_t _discard_cnt;
    card **_deck;
    int32_t _deck_cnt; // if = 0 shuffle from _discard
    char *_logfile_name;
} game;

#include "game.h"

#endif