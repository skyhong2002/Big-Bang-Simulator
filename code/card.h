#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _card
{
    uint8_t _suit; // 1 spade 2 heart 3 diamond 4 club
    uint8_t _number;
    char *_name;
    char *_skill;
} card;

#define VOLCANIC "VOLCANIC", "Equipment: 2-distance gun (unlimited BANG)"
#define SCHOFIELD "SCHOFIELD", "Equipment: 2-distance gun"
#define REMINGTON "REMINGTON", "Equipment: 3-distance gun"
#define REV_CARABINE "REV. CARABINE", "Equipment: 4-distance gun"
#define DINAMITE "DINAMITE", "Equipment: When you start your next turn (you have the Dynamite already in play), before the first phase you must \"draw!\":\nif you draw a card showing Spades and a number between 2 and 9, the Dynamite explodes! Discard it and lose 3 life points;\notherwise, pass the Dynamite to the player on your left (who will \"draw!\" on his turn, etc)"
#define PRIGIONE "PRIGIONE", "Equipment: Play this card in front of any player regardless of the distance: you put him in jail! If you are in jail, you must \"draw!\" before the beginning of your turn:\nif you draw a Heart card, you escape from jail: discard the Jail, and continue your turn as normal;\notherwise discard the Jail and skip your turn."
#define MUSTANG "MUSTANG", "Equipment: The distance between other players and you is increased by 1(other watch you)"

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

#define APPALOOSA "APPALOOSA", "Facility: Distance from other players minus one"
#define WINCHESTER "WINCHESTER", "Facility: 5-distance gun"
#define DILIGENZA "DILIGENZA", "Facility: Draw 2 cards from the deck"
#define BARILE "BARILE", "Facility: prevent from card heart"
#define INDIANI "INDIANI", "Facility:who played this card, may discard a BANG, or lose one life point"

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
const card CARD_18 = {1, 12, BARILE};
const card CARD_19 = {1, 13, SCHOFIELD};
const card CARD_20 = {1, 13, BARILE};
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

const card *const CARD[80] = {
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