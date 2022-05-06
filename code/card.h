#pragma once

#include<stdint.h>
#include<stdbool.h>

typedef struct _card{
    uint8_t _suit; //1 space 2 heart 3 diamond 4 club
    uint8_t _number;
    char *_name;
    uint8_t _type; //0 handcard 1 equipment
    char *_feature;
    /* 
     * bang
     * throw
     * draw
     * missed
     * specify_palyer_nodis
     * others_players
     * plus_hp
     * specify_palyer_dis
     * plus_dis
     * distance
     * minus_dis
     */
    special *_spec;
    uint8_t _judgment; // 0 none 1 suit 2 suit+number
    char *_skill;
}card;

typedef struct _special{
    bool _is_none;
    bool _is_volcanic;
    bool _is_jail;
    bool _is_duello;
    bool _is_emporio;
    bool _is_dinamite;
    bool _is_indianii;
}special