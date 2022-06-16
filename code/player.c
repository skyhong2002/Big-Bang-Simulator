#include "player.h"
#include <stdlib.h>

int8_t getPosition(const player *p)
{
    return p->_position;
}

int8_t getHP(const player *p)
{
    return p->_hp;
}

bool isDead(const player *p) //return (p,hp == 0);
{
    if (p->_hp < 0 || p->_hp == 0)
    {
        return true;
    }
    return false;
}

int8_t getHandcardCnt(const player *p)
{
    return (p->_hand_cnt);
}

card *getHandcardInfo(const player *p, const int8_t cardID)
{
    return (p->_hand[cardID]);
}

card *getGunInfo(const player *p)
{
    printf("%s\n", p->_gun->_name);
    printf("%s\n", p->_gun->_skill);
    return (p->_gun);
}

card *getHorseInfo(const player *p)
{
    printf("%s\n", p->_horse->_name);
    printf("%s\n", p->_horse->_skill);
    return (p->_horse);
}

card *getJailInfo(const player *p)
{
    printf("%s\n", p->_jail->_name);
    printf("%s\n", p->_jail->_skill);
    return (p->_jail);
}

card *getDinamiteInfo(const player *p)
{
    printf("%s\n", p->_dinamite->_name);
    printf("%s\n", p->_dinamite->_skill);
    return (p->_dinamite);
}

card *getBarrelInfo(const player *p)
{
    printf("%s\n", p->_barrel->_name);
    printf("%s\n", p->_barrel->_skill);
    return (p->_barrel);
}

bool equip(player *p, card *c)
{
    if (p == NULL || c == NULL)
    {
        return false;
    }
    if (strncmp("VOLCANIC", c->_name, 8) == 0 || strncmp("SCHOFIELD", c->_name, 9) == 0 || strncmp("REMINGTON", c->_name, 9) == 0 || strncmp("REV. CARABINE", c->_name, 13) == 0 || strncmp("WINCHESTER", c->_name, 10) == 0)
    {
        p->_gun = c;
    }
    else if (strncmp("MUSTANG", c->_name, 7) == 0 || strncmp("APPALOOSA", c->_name, 9) == 0)
    {
        p->_horse = c;
    }
    else if (strncmp("PRIGIONE", c->_name, 8) == 0 && strncmp("Sceriffo",p->_identity,8)!=0)
    {
        p->_jail = c;
    }
    else if (strncmp("DINAMITE", c->_name, 8) == 0)
    {
        p->_dinamite = c;
    }
    else if (strncmp("BARREL", c->_name, 6) == 0)
    {
        p->_barrel = c;
    }
    else
    {
        return false;
    }
    return true;
}
bool draw(player *p, game *game)
{
    if (p == NULL || game == NULL)
    {
        return false;
    }
    p->_hand_cnt += 1;

    p->_hand[p->_hand_cnt - 1] = game->_deck[game->_deck_cnt - 1];
    game->_deck_cnt -= 1;
    if(game->_deck_cnt==0)
    {
        shuffle(game);
    }
    return true;
}
//  equip: 1 or hand: 2
// I need discard_cnt !
// sure the discard size is bigger enough?
bool discard(player *p, card *c, int8_t type, game *game)
{
    if (p == NULL || c == NULL)
    {
        return false;
    }
    if (type == 1)
    {
        game->_discard[game->_discard_cnt] = c;
        c = NULL;
    }
    else if (type == 2)
    {
        for (int32_t i = 0; i < p->_hand_cnt; i++)
        {
            if (p->_hand[i] == c)
            {
                game->_discard[game->_discard_cnt] = c;
                c = NULL;
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
    }
    game->_discard_cnt += 1;
    return true;
}
bool changeHP(player *p, int8_t hp)
{
    if (p == NULL)
    {
        return false;
    }
    if (p->_hp + hp <= p->_max_hp)
    {
        p->_hp += hp;
    }
    return true;
}
