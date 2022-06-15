#include "player.h"

int32_t player_id=0;
int32_t player_position=1;
int32_t player_maxhp=0;
int32_t player_hp=0;
int32_t player_hand_cnt=0;
int32_t player_hand=0;
int32_t player_gun=0;
int32_t player_horse=0;
int32_t player_jail=0;
int32_t player_dinamite=0;
int32_t player_barrel=0;
bool playerInit(player *p, int8_t maxhp, char *identity, role *role)
{
    p = calloc(1,sizeof(player));
    p->_id = player_id ;
    player_id=player_id+1;

    p->_position=player_position;
    player_position=player_position+1;

    p->_role = role;

    p->_identity = identity;

    p->_max_hp = maxhp;

    p->_hp=player_hp;

    p->_hand_cnt=player_hand_cnt;







    p->_hand = hand;

    p->_gun = player_gun;

    p->_horse = player_horse;

    p->_jail = player_jail;

    p->_dinamite = player_dinamite;

    p->_barrel = player_barrel;

    return true;

}
int8_t getPosition(const player *p)
{
    return p->_position;
}
    
int8_t getHP(const player *p)
{
    return p->_hp;
}
    
bool isDead(const player *p)//return (p,hp == 0);
{
    if(p->_hp<0 || p->_hp==0)
    {
        return true;
    }
    return false;
}
    
int8_t getHandcardCnt(const player *p)
{
    return (p->_hand);
}
    
card *getHandcardInfo(const player *p, const int8_t cardID)
{
    return (p->_hand_cnt,p->_id);
}
    
card *getGunInfo(const player *p)
{
    return(p->_gun);
}
    
card *getHourseInfo(const player *p)
{
    return(p->_horse);
}
    
card *getJailInfo(const player *p)
{
    return(p->_jail);
}
    
card *getDinamiteInfo(const player *p)
{
    return(p->_dinamite);
}
   
card *getBarrelInfo(const player *p)
{
    return(p->_barrel);
}
    
bool equip(player *p, card *c);
bool draw(player *p, card *c);
bool discard(player *p, card *c);
bool changeHP(player *p, int8_t hp); // -3 炸藥 -1 被射 +1 酒