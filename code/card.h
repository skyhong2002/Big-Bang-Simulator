#pragma once

#ifndef _CARD_H_
#define _CARD_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "structure.h"
#include "game.h"
#include "player.h"

bool bang(player *me, card *c, player *target, game *game);
bool panic(player *me, card *c, player *target, game *game);
bool catBalou(player *me, card *c, player *target, game *game);
bool duel(player *me, card *c, player *target, game *game);

bool missed(player *me, card *c, game *game);

bool stageCoach(player *me, card *c, game *game);
bool wellsFargo(player *me, card *c, game *game);
bool beer(player *me, card *c, game *game);
bool saloon(player *me, card *c, game *game);
bool generalStore(player *me, card *c, game *game);
bool gatling(player *me, card *c, game *game);
bool indians(player *me, card *c, game *game);

void checkDistance(int32_t *between, int32_t *cD, player *me, player *target, game *game);
bool drawplayer(player *me, player *target, int8_t choice);
bool throwaway(player *me, player *target, int8_t choice, game *game);

#endif