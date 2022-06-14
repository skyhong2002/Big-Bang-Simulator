#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #include "code/game.h"
// #include "code/card.h"
// #include "code/player.h"
// #include "code/role.h"
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
#define BANG "BANG", "Action: BANG someone within distace"
#define MANCATO "MANCATO", "Action: prevent from BANGed"
const card CARD_02 = {1, 1, BANG};
const card CARD_03 = {1, 2, MANCATO};
int main()
{
    printf("BANG!");
    card test = CARD_02;
    card test2 = CARD_03;
    player p1;
    p1._hand = calloc(100, 100);
    p1._hand[0] = calloc(1, sizeof(card));
    p1._hand[1] = calloc(1, sizeof(card));
    **p1._hand = test;
    printf("%s\n", (**p1._hand)._name);
    *(*p1._hand + 1) = test2;
    printf("%s\n", (*(*p1._hand + 1))._name);

    return 0;
}
