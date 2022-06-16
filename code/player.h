#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "card.h"
#include "role.h"

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

bool playerInit(player *p, int8_t maxhp, char *identity, role *role);
int8_t getPosition(const player *p);
int8_t getHP(const player *p); // return hp
bool isDead(const player *p);  //return (p._hp == 0);
int8_t getHandcardCnt(const player *p);
card *getHandcardInfo(const player *p, const int8_t cardID); // 0 ~ _hand_cnt-1
card *getGunInfo(const player *p);
card *getHourseInfo(const player *p);
card *getJailInfo(const player *p);
card *getDinamiteInfo(const player *p);
card *getBarrelInfo(const player *p);
bool equip(player *p, card *c);
bool draw(player *p, game *game);
bool discard(player *p, card *c, int8_t type, game *game);
bool changeHP(player *p, int8_t hp); // -3 炸藥 -1 被射 +1 酒

#endif