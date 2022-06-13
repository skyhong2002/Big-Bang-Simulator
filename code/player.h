#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "role.h"
#include "card.h"

typedef struct _player
{
    uint8_t _id;
    uint8_t _position; // 角色位置
    role *_role;
    char *_identity; // Sceriffo, Vice, Fuorilegge, Rinnegato
    int8_t _max_hp;  // after checking the role is Sceriffo or not
    int8_t _hp;
    uint8_t _hand_cnt; // must not higher than _hp at the end of round
    card **_hand;
    card *_gun;   // 0, 1, 2, 3, 4, 5
    card *_horse; // -1, 0, 1
    card *_jail;
    card *_dinamite;
    card *_barrel;
} player;