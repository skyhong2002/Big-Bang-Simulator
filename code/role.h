#ifndef _ROLE_H_
#define _ROLE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

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

typedef struct _role
{
    const char *_name;  //名稱
    const char *_skill; //功能
    uint8_t _lvalue;    //生命值
} role;

const role ROLE_01 = {WillyTheKid, 4};
const role ROLE_02 = {Jourdonnais, 4};
const role ROLE_03 = {SlabTheKiller, 4};
const role ROLE_04 = {CalamityJanet, 4};
const role ROLE_05 = {JesseJones, 4};
const role ROLE_06 = {ElGringo, 3};
const role ROLE_07 = {PaulRegret, 3};
const role ROLE_08 = {SidKetchum, 4};
const role ROLE_09 = {BlackJack, 4};
const role ROLE_10 = {SuzyLafayette, 4};
const role ROLE_11 = {RoseDoolan, 4};
const role ROLE_12 = {VultureSam, 4};
const role ROLE_13 = {BartCassidy, 4};
const role ROLE_14 = {KitCarlaon, 4};
const role ROLE_15 = {PedroRamirez, 4};
const role ROLE_16 = {LuckyDuke, 4};

const role *const ROLE[16] = {
    &ROLE_01, &ROLE_02, &ROLE_03, &ROLE_04,
    &ROLE_05, &ROLE_06, &ROLE_07, &ROLE_08,
    &ROLE_09, &ROLE_10, &ROLE_11, &ROLE_12,
    &ROLE_13, &ROLE_14, &ROLE_15, &ROLE_16};

#endif