#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "structure.h"
#include "player.h"
#include "card.h"

void saveLogInit(game *bang);
int32_t getOption(game *bang, player *p);
int32_t getAction(game *bang, card *c);
char *gameloop(game *bang);
char *isGameEnd(game *bang);
void saveLog(char *message);
void displayPlayer(const player *p);
void displayHandCard(const player *p);
char *displayAction(const player *p, card *c, int32_t type); // 1: Success 2: Fail 3: Action: 4: Warning 5: Drawok 6: Drawnotok 7: Discardok 8: Discardnotok 9: drawnoplayer 0: Nocards
char *judge(player *p, card *c, game *game);

#endif