#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct _card
{
    uint8_t _suit; // 1 space 2 heart 3 diamond 4 club
    uint8_t _number;
    char *_name;
    char *_skill;
} card;

#define VOLCANIC "VOLCANIC", "Equipment: 2-distance gun (unlimited BANG)"
#define SCHOFIELD "SCHOFIELD", "Equipment: 2-distance gun"
#define REMINGTON "REMINGTON", "Equipment: 3-distance gun"
#define REV_CARABINE "REV. CARABINE", "Equipment: 4-distance gun"

#define BANG "BANG", "Action: BANG someone within distace"
#define MANCATO "MANCATO", "Action: prevent from BANGed"
#define DUELLO "DUELLO", "Action: draw BANG until the one can't draw HP-1"
#define EMPORIO "EMPORIO", "Action: Everyone gets a card (雜貨鋪)"

const card CARD_61 = { 4, 1, REV_CARABINE };
const card CARD_62 = { 4, 1, MANCATO };
const card CARD_63 = { 4, 2, BANG };
const card CARD_64 = { 4, 3, BANG };
const card CARD_65 = { 4, 4, BANG };
const card CARD_66 = { 4, 5, BANG };
const card CARD_67 = { 4, 6, BANG };
const card CARD_68 = { 4, 7, BANG };
const card CARD_69 = { 4, 8, DUELLO };
const card CARD_70 = { 4, 8, BANG };
const card CARD_71 = { 4, 9, EMPORIO };
const card CARD_72 = { 4, 9, BANG };
const card CARD_73 = { 4, 10, MANCATO };
const card CARD_74 = { 4, 10, VOLCANIC };
const card CARD_75 = { 4, 11, MANCATO };
const card CARD_76 = { 4, 11, SCHOFIELD };
const card CARD_77 = { 4, 12, SCHOFIELD };
const card CARD_78 = { 4, 12, MANCATO };
const card CARD_79 = { 4, 13, MANCATO };
const card CARD_80 = { 4, 13, REMINGTON };

const card *const CARD[80] = {
    &CARD_61, &CARD_62, &CARD_63, &CARD_64, &CARD_65, 
    &CARD_66, &CARD_67, &CARD_68, &CARD_69, &CARD_70, 
    &CARD_71, &CARD_72, &CARD_73, &CARD_74, &CARD_75, 
    &CARD_76, &CARD_77, &CARD_78, &CARD_79, &CARD_80};