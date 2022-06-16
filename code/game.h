#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "structure.h"
#include "player.h"
#include "card.h"

int32_t gameloop(game *bang);
char* isGameEnd(const game *bang);
void displayPlayer(const player *p);
void displayHandCard(const player *p);
void displayAction(const player *p, card *c);
bool judge(player* p, card *c, game* game); //判定

#endif