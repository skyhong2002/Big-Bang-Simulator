#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "structure.h"
#include "player.h"
#include "card.h"



void gameInit(game *bang);
int32_t gameEnd(game *bang);
void shuffle(game *bang);
void displayPlayer(const player *player);
void displayHandCard(const player *player);
void displayAction(const player *player, card *c);
card *judge(card **deck); //判定

#endif