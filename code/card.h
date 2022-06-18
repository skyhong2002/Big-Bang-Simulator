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

char *bangAction(player *me, card *c, player *target, game *game);
char *panic(player *me, card *c, player *target, game *game);
char *catBalou(player *me, card *c, player *target, game *game);
char *duel(player *me, card *c, player *target, game *game);

char *missed(player *me, card *c, game *game);

char *stageCoach(player *me, card *c, game *game);
char *wellsFargo(player *me, card *c, game *game);
char *beer(player *me, card *c, game *game);
char *saloon(player *me, card *c, game *game);
char *generalStore(player *me, card *c, game *game);
char *gatling(player *me, card *c, game *game);
char *indians(player *me, card *c, game *game);

void checkDistance(int32_t *between, int32_t *cD, player *me, player *target, game *game);
bool drawplayer(player *me, player *target, int8_t choice);
bool throwaway(player *me, player *target, int8_t choice, game *game);

#endif