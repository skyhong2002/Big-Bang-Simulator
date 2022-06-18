#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "structure.h"
#include "card.h"

int8_t getPosition(const player *p);
int8_t getHP(const player *p); // return hp
bool isDead(const player *p);  // return (p._hp == 0);
int8_t getHandcardCnt(const player *p);
card *getHandcardInfo(const player *p, const int8_t cardID); // 0 ~ _hand_cnt-1
card *getGunInfo(const player *p);
card *getHorseInfo(const player *p);
card *getJailInfo(const player *p);
card *getDinamiteInfo(const player *p);
card *getBarrelInfo(const player *p);
char *equip(player *me, card *c, player *target, game* game);
char *draw(player *p, game *game);
void shuffle(game *bang); // TBD
char* discard(player *p, card *c, int8_t type, game *game);
bool changeHP(player *p, int8_t hp); // -3 炸藥 -1 被射 +1 酒

#endif