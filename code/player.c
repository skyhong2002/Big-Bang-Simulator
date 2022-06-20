#include "player.h"
#include <stdlib.h>

int8_t getPosition(const player *p) {
    return p->_position;
}

int8_t getHP(const player *p) {
    return p->_hp;
}

bool isDead(const player *p) // return (p,hp == 0);
{
    if (p->_hp < 0 || p->_hp == 0) {
        printf("Player %s is dead 🏴‍☠️ ( ´･･)ﾉ(._.`)\n", p->_name);
        return true;
    }
    return false;
}

int8_t getHandcardCnt(const player *p) {
    return (p->_hand_cnt);
}

card *getHandcardInfo(const player *p, const int8_t cardID) {
    return (p->_hand[cardID]);
}

card *getGunInfo(const player *p) {
    printf("%s\n", p->_gun->_name);
    printf("%s\n", p->_gun->_skill);
    return (p->_gun);
}

card *getHorseInfo(const player *p) {
    printf("%s\n", p->_horse->_name);
    printf("%s\n", p->_horse->_skill);
    return (p->_horse);
}

card *getJailInfo(const player *p) {
    printf("%s\n", p->_jail->_name);
    printf("%s\n", p->_jail->_skill);
    return (p->_jail);
}

card *getDinamiteInfo(const player *p) {
    printf("%s\n", p->_dinamite->_name);
    printf("%s\n", p->_dinamite->_skill);
    return (p->_dinamite);
}

card *getBarrelInfo(const player *p) {
    printf("%s\n", p->_barrel->_name);
    printf("%s\n", p->_barrel->_skill);
    return (p->_barrel);
}

char *equip(player *me, card *c, player *target, game *game) {
    if (me == NULL || c == NULL) {
        return displayAction(me, c, 2);
    }
    if ((strncmp("VOLCANIC", c->_name, 8) == 0 || strncmp("SCHOFIELD", c->_name, 9) == 0 || strncmp("REMINGTON", c->_name, 9) == 0 || strncmp("REV. CARABINE", c->_name, 13) == 0 || strncmp("WINCHESTER", c->_name, 10) == 0)) {
        if (target->_gun != NULL) {
            discard(me, target->_gun, 1, game);
        }
        target->_gun = c;
    }
    else if ((strncmp("MUSTANG", c->_name, 7) == 0 || strncmp("APPALOOSA", c->_name, 9) == 0) ) {
        if (target->_horse != NULL) {
            discard(me, target->_horse, 1, game);
        }
        target->_horse = c;
    }
    else if ((strncmp("PRIGIONE", c->_name, 8) == 0 && strncmp("Sceriffo", target->_identity, 8) != 0) && target->_jail == NULL) {
        if (target->_jail != NULL) {
            discard(me, target->_jail, 1, game);
        }
        target->_jail = c;
    }
    else if ((strncmp("DINAMITE", c->_name, 8) == 0)) {
        if (target->_dinamite != NULL) {
            discard(me, target->_dinamite, 1, game);
        }
        target->_dinamite = c;
    }
    else if ((strncmp("BARREL", c->_name, 6) == 0) && target->_barrel == NULL) {
        if (target->_barrel != NULL) {
            discard(me, target->_barrel, 1, game);
        }
        target->_barrel = c;
    }
    else
    {
        return displayAction(me, c, 4);
    }
    // printf("equip success\n");
    discard(me, c, 2, game);
    return displayAction(me, c, 3);
}
char *draw(player *p, game *game) {
    if (p == NULL || game == NULL) {
        return displayAction(p, NULL, 6);
    }
    p->_hand_cnt += 1;
    // printf("Deck cnt: %d\n", game->_deck_cnt);
    p->_hand[p->_hand_cnt - 1] = game->_deck[game->_deck_cnt - 1];
    // printf("draw one\n");
    game->_deck_cnt -= 1;
    // printf("change card num\n");
    if (game->_deck_cnt == 0) {
        shuffle(game);
    }
    if (p->_name == NULL) {
        return displayAction(p, NULL, 9);
    }
    // printf("return draw card\n");
    return displayAction(p, NULL, 5);
}
//  equip: 1 or hand: 2
// I need discard_cnt !
// sure the discard size is bigger enough?
char *discard(player *p, card *c, int8_t type, game *game) {
    if (p == NULL || c == NULL) {
        return displayAction(p, c, 8);
    }
    if (type == 1) {
        // printf("in discard\n");
        game->_discard[game->_discard_cnt] = c;
        // static card* tempt1 = NULL;
        // c = tempt1;
        // printf("c: %p\n", c);
    }
    else if (type == 2) {
        for (int32_t i = 0; i < p->_hand_cnt; i++) {
            if (p->_hand[i] == c)
            {
                game->_discard[game->_discard_cnt] = c;
                // c = NULL;
                // printf("i: %d\n", i);
                for (int32_t j = i; j < p->_hand_cnt; j++)
                {
                    if (j + 1 != p->_hand_cnt)
                    {
                        p->_hand[j] = p->_hand[j + 1];
                    }
                    else
                    {
                        break;
                    }
                }
                break;
            }
        }
        p->_hand_cnt -= 1;
        if (strncmp(p->_role->_name, "SuzyLafayette", 13) == 0 && p->_hand_cnt == 0) {
            printf("When SuzyLafayette no cards, draw a card.\n");
            draw(p, game);
        }
    }
    game->_discard_cnt += 1;
    // printf("discard card name\n");
    // for(int32_t i = 0; i<game->_discard_cnt; i++)
    // {
    //     printf("%s\n", game->_discard[i]->_name);
    // }
    // printf("already return\n");
    // printf("c adress: %p\n", game->_discard[game->_discard_cnt - 1]);
    return displayAction(p, game->_discard[game->_discard_cnt - 1], 7);
}
bool changeHP(player *p, int8_t hp, game *game) {
    if (strncmp(p->_role->_name, "BartCassidy", 11) == 0 && hp < 0) {
        printf("Because Player %s is BartCassidy, so BartCassidy can draw %d card(s)\n", p->_name, abs(hp));
        for (int32_t i = 0; i < abs(hp); i++)
            draw(p, game);
    }
    char mes[100] = {0};
    char strhp[2] = {0};
    if (hp < 0) {
        strhp[0] = '-';
        strhp[1] = (-hp) + '0';
    }
    else
    {
        strhp[0] = hp + '0';
    }

    if (p == NULL) {
        return false;
    }
    if (p->_hp + hp <= p->_max_hp) {
        p->_hp += hp;
    }
    strcat(mes, "Player ");
    strcat(mes, p->_name);
    strcat(mes, " HP change ");
    if (hp < 0)
        strcat(mes, "-");
    char tmp[2] = {0};
    tmp[0] = abs(hp) + '0';
    strcat(mes, tmp);
    strcat(mes, ". Now HP: ");
    if (p->_hp < 0)
        strcat(mes, "-");
    tmp[0] = abs(p->_hp) + '0';
    strcat(mes, tmp);
    printf("Change: %s\n", mes);
    saveLog(mes);
    return true;
}
