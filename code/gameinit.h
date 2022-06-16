#ifndef _GAMEINIT_H_
#define _GAMEINIT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "structure.h"

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

const card CARD_01 = {1, 1, APPALOOSA};
const card CARD_02 = {1, 1, BANG};
const card CARD_03 = {1, 2, MANCATO};
const card CARD_04 = {1, 3, MANCATO};
const card CARD_05 = {1, 4, MANCATO};
const card CARD_06 = {1, 5, MANCATO};
const card CARD_07 = {1, 6, MANCATO};
const card CARD_08 = {1, 7, MANCATO};
const card CARD_09 = {1, 8, MANCATO};
const card CARD_10 = {1, 8, WINCHESTER};
const card CARD_11 = {1, 9, DILIGENZA};
const card CARD_12 = {1, 9, DILIGENZA};
const card CARD_13 = {1, 10, VOLCANIC};
const card CARD_14 = {1, 10, PRIGIONE};
const card CARD_15 = {1, 11, DUELLO};
const card CARD_16 = {1, 11, PRIGIONE};
const card CARD_17 = {1, 12, EMPORIO};
const card CARD_18 = {1, 12, BARREL};
const card CARD_19 = {1, 13, SCHOFIELD};
const card CARD_20 = {1, 13, BARREL};
const card CARD_21 = {2, 1, BANG};
const card CARD_22 = {2, 1, PANICOI};
const card CARD_23 = {2, 2, DINAMITE};
const card CARD_24 = {2, 3, WELLSFARGO};
const card CARD_25 = {2, 4, PRIGIONE};
const card CARD_26 = {2, 5, SALOON};
const card CARD_27 = {2, 6, BIRRA};
const card CARD_28 = {2, 7, BIRRA};
const card CARD_29 = {2, 8, BIRRA};
const card CARD_30 = {2, 8, MUSTANG};
const card CARD_31 = {2, 9, BIRRA};
const card CARD_32 = {2, 9, MUSTANG};
const card CARD_33 = {2, 10, GATLING};
const card CARD_34 = {2, 10, BIRRA};
const card CARD_35 = {2, 11, BIRRA};
const card CARD_36 = {2, 11, PANICOI};
const card CARD_37 = {2, 12, BANG};
const card CARD_38 = {2, 12, PANICOI};
const card CARD_39 = {2, 13, CATBALOU};
const card CARD_40 = {2, 13, BANG};
const card CARD_41 = {3, 1, BANG};
const card CARD_42 = {3, 2, INDIANI};
const card CARD_43 = {3, 2, BANG};
const card CARD_44 = {3, 3, BANG};
const card CARD_45 = {3, 4, BANG};
const card CARD_46 = {3, 5, BANG};
const card CARD_47 = {3, 6, BANG};
const card CARD_48 = {3, 7, BANG};
const card CARD_49 = {3, 8, PANICOI};
const card CARD_50 = {3, 8, BANG};
const card CARD_51 = {3, 9, BANG};
const card CARD_52 = {3, 9, CATBALOU};
const card CARD_53 = {3, 10, BANG};
const card CARD_54 = {3, 10, CATBALOU};
const card CARD_55 = {3, 11, BANG};
const card CARD_56 = {3, 11, CATBALOU};
const card CARD_57 = {3, 12, BANG};
const card CARD_58 = {3, 12, DUELLO};
const card CARD_59 = {3, 13, INDIANI};
const card CARD_60 = {3, 13, BANG};
const card CARD_61 = {4, 1, REV_CARABINE};
const card CARD_62 = {4, 1, MANCATO};
const card CARD_63 = {4, 2, BANG};
const card CARD_64 = {4, 3, BANG};
const card CARD_65 = {4, 4, BANG};
const card CARD_66 = {4, 5, BANG};
const card CARD_67 = {4, 6, BANG};
const card CARD_68 = {4, 7, BANG};
const card CARD_69 = {4, 8, DUELLO};
const card CARD_70 = {4, 8, BANG};
const card CARD_71 = {4, 9, EMPORIO};
const card CARD_72 = {4, 9, BANG};
const card CARD_73 = {4, 10, MANCATO};
const card CARD_74 = {4, 10, VOLCANIC};
const card CARD_75 = {4, 11, MANCATO};
const card CARD_76 = {4, 11, SCHOFIELD};
const card CARD_77 = {4, 12, SCHOFIELD};
const card CARD_78 = {4, 12, MANCATO};
const card CARD_79 = {4, 13, MANCATO};
const card CARD_80 = {4, 13, REMINGTON};

#define NO_CARD CARD[0]

const card *const CARD[81] = {NULL,
                              &CARD_01, &CARD_02, &CARD_03, &CARD_04, &CARD_05,
                              &CARD_06, &CARD_07, &CARD_08, &CARD_09, &CARD_10,
                              &CARD_11, &CARD_12, &CARD_13, &CARD_14, &CARD_15,
                              &CARD_16, &CARD_17, &CARD_18, &CARD_19, &CARD_20,
                              &CARD_21, &CARD_22, &CARD_23, &CARD_24, &CARD_25,
                              &CARD_26, &CARD_27, &CARD_28, &CARD_29, &CARD_30,
                              &CARD_31, &CARD_32, &CARD_33, &CARD_34, &CARD_35,
                              &CARD_36, &CARD_37, &CARD_38, &CARD_39, &CARD_40,
                              &CARD_41, &CARD_42, &CARD_43, &CARD_44, &CARD_45,
                              &CARD_46, &CARD_47, &CARD_48, &CARD_49, &CARD_50,
                              &CARD_51, &CARD_52, &CARD_53, &CARD_54, &CARD_55,
                              &CARD_56, &CARD_57, &CARD_58, &CARD_59, &CARD_60,
                              &CARD_61, &CARD_62, &CARD_63, &CARD_64, &CARD_65,
                              &CARD_66, &CARD_67, &CARD_68, &CARD_69, &CARD_70,
                              &CARD_71, &CARD_72, &CARD_73, &CARD_74, &CARD_75,
                              &CARD_76, &CARD_77, &CARD_78, &CARD_79, &CARD_80};
const role *ROLE[16];

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

void roleInit(){
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

    ROLE[0] = &ROLE_01;
    ROLE[1] = &ROLE_02;
    ROLE[2] = &ROLE_03;
    ROLE[3] = &ROLE_04;
    ROLE[4] = &ROLE_05;
    ROLE[5] = &ROLE_06;
    ROLE[6] = &ROLE_07;
    ROLE[7] = &ROLE_08;
    ROLE[8] = &ROLE_09;
    ROLE[9] = &ROLE_10;
    ROLE[10] = &ROLE_11;
    ROLE[11] = &ROLE_12;
    ROLE[12] = &ROLE_13;
    ROLE[13] = &ROLE_14;
    ROLE[14] = &ROLE_15;
    ROLE[15] = &ROLE_16;

    /* ROLE = {
        &ROLE_01, &ROLE_02, &ROLE_03, &ROLE_04,
        &ROLE_05, &ROLE_06, &ROLE_07, &ROLE_08,
        &ROLE_09, &ROLE_10, &ROLE_11, &ROLE_12,
        &ROLE_13, &ROLE_14, &ROLE_15, &ROLE_16};*/
}

#endif