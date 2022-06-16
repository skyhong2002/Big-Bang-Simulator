#include "bang.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "player.h"

void deckInit(game *game)
{
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

    srand(time(NULL));
    int32_t shuff[80] = {0};
    int32_t x = 0;
    game->_discard = calloc(80, sizeof(card *));
    game->_deck = calloc(80, sizeof(card *));
    game->_discard_cnt = 0;
    game->_deck_cnt = 80;

    for (int32_t i = 0; i < 80; i++)
    {
        game->_discard[i] = calloc(1, sizeof(card));
        game->_deck[i] = calloc(1, sizeof(card));
        shuff[i] = i + 1;
    }

    for (int32_t i = 79; i >= 1; i--)
    {
        int32_t tempt = 0;
        // printf("%d\n", i);
        x = rand() % (i);
        tempt = shuff[i];
        shuff[i] = shuff[x];
        shuff[x] = tempt;
        game->_deck[i] = (card *)(CARD[shuff[i]]);
    }
    // printf("ok?\n");
    game->_deck[0] = (card *)(CARD[shuff[0]]);
    return;
}

int32_t player_id = 0;
int32_t player_position = 1;
int8_t checkrole[16] = {0};
int8_t checkiden[7] = {0};

bool playerInit(player *p, char *name, char *identity, game *game, const role **ROLE)
{

    p = calloc(1, sizeof(player));
    p->_id = player_id;
    player_id = player_id + 1;

    p->_name = name;
    if (p->_name == NULL)
        p->_name = "John Doe";

    p->_position = player_position;
    player_position = player_position + 1;
    int32_t x = 0;
    while (1)
    {
        srand(time(NULL));
        x = rand() % 16;
        if (checkrole[x] == 1)
        {
            continue;
        }
        else
        {
            checkrole[x] = 1;
            break;
        }
    }

    p->_hand = calloc(20, sizeof(card *));
    for (int32_t i = 0; i < 20; i++)
    {
        p->_hand[i] = calloc(1, sizeof(card));
    }
    p->_role = (role *)(ROLE[x]);
    p->_identity = identity;
    p->_max_hp = p->_role->_lvalue;
    p->_hp = p->_role->_lvalue;
    // p->_hand_cnt = role->_lvalue

    p->_hand = calloc(1, sizeof(card *));
    for (int32_t i = 0; i < p->_role->_lvalue; i++)
    {
        draw(p, game);
    }

    return true;
}

void gameInit(game *bang, int32_t pcnt, char *pname)
{
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

    const role *ROLE[16] = {
        &ROLE_01, &ROLE_02, &ROLE_03, &ROLE_04,
        &ROLE_05, &ROLE_06, &ROLE_07, &ROLE_08,
        &ROLE_09, &ROLE_10, &ROLE_11, &ROLE_12,
        &ROLE_13, &ROLE_14, &ROLE_15, &ROLE_16};
    // printf("deckInit success\n");
    deckInit(bang);
    printf("deckInit success\n");
    bang->_total_card_cnt = 80; // = 80
    bang->_total_player_cnt = pcnt;
    bang->_alive_player_cnt = pcnt;
    bang->_turn = 0;

    char *namelist[] = {
        pname, "Akira", "Bob", "Cloud", "Dora", "Eren", "Freya", "Genious", "Haiya"};

    char *iden[] = {
        "Sceriffo", "Fuorilecce", "Fuorilecce", "Rinnecato", "Vice", "Fuorilecce", "Vice"};

    for (int i = 0; i < bang->_total_player_cnt; ++i)
    {
        int32_t x = 0;
        while (1)
        {
            srand(time(NULL));
            x = rand() % pcnt;
            if (checkiden[x] == 1)
            {
                continue;
            }
            else
            {
                checkiden[x] = 1;
                break;
            }
        }
        playerInit(&bang->_player[i], namelist[x], iden[0], bang, ROLE);
    }
}