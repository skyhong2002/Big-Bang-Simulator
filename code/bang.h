#pragma once

#ifndef _BANG_H_
#define _BANG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "structure.h"

void gameInit(game *bang);
void deckInit(game *game);
bool playerInit(player *p, char *identity, game *game, role **ROLE);

/* CARD */

#define VOLCANIC "VOLCANIC", "Equipment: 1-distance gun (unlimited BANG)"
#define SCHOFIELD "SCHOFIELD", "Equipment: 2-distance gun"
#define REMINGTON "REMINGTON", "Equipment: 3-distance gun"
#define REV_CARABINE "REV. CARABINE", "Equipment: 4-distance gun"
#define WINCHESTER "WINCHESTER", "Equipment: 5-distance gun"

#define DINAMITE "DINAMITE", "Equipment: When you start your next turn (you have the Dynamite already in play), before the first phase you must \"draw!\":\nif you draw a card showing Spades and a number between 2 and 9, the Dynamite explodes! Discard it and lose 3 life points;\notherwise, pass the Dynamite to the player on your left (who will \"draw!\" on his turn, etc)"
#define PRIGIONE "PRIGIONE", "Equipment: Play this card in front of any player regardless of the distance: you put him in jail! If you are in jail, you must \"draw!\" before the beginning of your turn:\nif you draw a Heart card, you escape from jail: discard the Jail, and continue your turn as normal;\notherwise discard the Jail and skip your turn."
#define MUSTANG "MUSTANG", "Equipment: The distance between other players and you is increased by 1(other watch you)"
#define APPALOOSA "APPALOOSA", "Equipment: Distance from other players minus one"
#define BARREL "BARREL", "Facility: prevent from card heart"

#define BANG "BANG", "Action: BANG someone within distace"
#define MANCATO "MANCATO", "Action: prevent from BANGed"
#define DUELLO "DUELLO", "Action: draw BANG until the one can't draw HP-1"
#define EMPORIO "EMPORIO", "Action: Everyone gets a card (雜貨鋪)"
#define PANICOI "PANICOI", "Action: Draw a card from a player at distance 1"
#define WELLSFARGO "WELLSFARGO", "Action: Draw three cards from the deck"
#define SALOON "SALOON", "Action: Regain your one life point or regain everyone one life points"
#define BIRRA "BIRRA", "Action: Regain your one life point"
#define GATLING "GATLING", "Action: Shoots a BANG! to all the other players"
#define CATBALOU "CATBALOU", "Action: Force any one player to discard a card"
#define DILIGENZA "DILIGENZA", "Action: Draw 2 cards from the deck"

#define INDIANI "INDIANI", "Facility: who played this card, may discard a BANG, or lose one life point"

/* ROLE */

#define WillyTheKid "WillyTheKid", "During his turn, he can play any number of \"Bang!\" cards."
#define Jourdonnais "Jourdonnais", "He is considered to have a \"Barrel\" in play at all times; he can \"Draw!\" when he is the target of a \"Bang!\", and on a Heart he is missed. If he has an actual \"Barrel\" card in play, he can count both of them, giving him two chances to cancel the \"Bang!\" before playing a \"Missed!\""
#define SlabTheKiller "SlabTheKiller", "Players trying to cancel his \"Bang!\" cards need to play 2 \"Missed!\". The \"Barrel\" effect, if successfully used, only counts as one \"Missed!\""
#define CalamityJanet "CalamityJanet", "She can use \"Bang!\" cards as \"Missed!\" cards and vice versa. She is still subject to \"Bang!\" limitations: If she plays a \"Missed!\" card as a \"Bang!\", she cannot play another \"Bang!\" card that turn (unless she has a Volcanic in play)."
#define JesseJones "JesseJones", "During phase 1 of his turn, he may choose to draw the first card from the deck, or randomly from the hand of any other player. Then he draws the second card from the deck."
#define ElGringo "ElGringo", "Each time he loses a life point due to a card played by another player, Gringo draws a random card from the hand of that player (one card for each life), unless he has no more hand cards."
#define PaulRegret "PaulRegret", "He is considered to have a \"Mustang\" in play at all times; all other players must add 1 to the distance to him. If he has an actual \"Mustang\" card in play, he can count both of them, increasing all distance to him by a total of 2."
#define SidKetchum "SidKetchum", "At any time, he may discard 2 cards from his hand to regain one life point. If he is willing and able to, he can use this ability more than once at a time."
#define BlackJack "BlackJack", "During phase 1 of his turn, he must show the second card he draws; on Hearts or Diamonds, he draws one additional card that turn (without revealing it)."
#define SuzyLafayette "SuzyLafayette", "Each time she has no cards in her hand, she instantly draws a card from the draw pile."
#define RoseDoolan "RoseDoolan", "She is considered to have a \"Appaloosa\" in play at all times; she sees the other players at a distance decreased by 1. If she has an actual \"Appaloosa\" card in play, she can count both of them, reducing her distance to all other players by a total of 2."
#define VultureSam "VultureSam", "Each time another player is eliminated, Sam takes all the cards that player had in his hand and in play, and adds them to his hand."
#define BartCassidy "BartCassidy", "Each time he loses a life point, he immediately draws a card from the deck."
#define KitCarlaon "KitCarlaon", "During his turn, he looks at the top three cards of the deck: he chooses 2 to draw, and puts the other one back on the top of the deck, face down."
#define PedroRamirez "PedroRamirez", "During his turn, he may choose to draw the first card from the top of the discard pile or from the deck. Then he draws the second card from the deck."
#define LuckyDuke "LuckyDuke", "Each time he is required to \"Draw!\", he flips the top two cards from the deck, and chooses the result he prefers. Discard both cards afterward."

#endif