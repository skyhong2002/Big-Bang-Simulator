#include "game.h"
#include <math.h>
#include <stdlib.h>

char* isGameEnd(const game *bang){
    bool Sceriffo = false;
    bool Fuorilecce = false;
    bool Rinnecato = false;
    for(int i = 0; i < bang->_total_player_cnt; ++i){
        if(isDead(&bang->_player[i])) continue;
        //"Sceriffo", "Fuorilecce", "Fuorilecce", "Rinnecato", "Vice", "Fuorilecce", "Vice"
        switch (bang->_player[i]._identity[0]){
        case 'S': // "Sceriffo"
        case 'V': // "Vice"
            Sceriffo = true;
            break;
        case 'F': // "Fuorilecce"
            Fuorilecce = true;
            break;
        case 'R': // "Rinnecato"
            Rinnecato = true;
            break;
        
        default:
            break;
        }
    }

    if(Sceriffo && !Fuorilecce && !Rinnecato){
        return "Sceriffo camp";
    }
    else if(!Sceriffo && Fuorilecce && !Rinnecato){
        return "Fuorilecce camp";
    }
    else if(!Sceriffo && !Fuorilecce && Rinnecato){
        return "Rinnecato";
    }
    return NULL;
}

int32_t gameloop(game *bang){
    int32_t total_turn = 0;
    char *winner = "Nobody";
    while(total_turn <= 10 && total_turn >= 0){
        ++total_turn;
        printf("\nTurn %d:\n", total_turn);

        player *cplayer = &bang->_player[bang->_turn]; //current player
        // get 2 card;
        displayPlayer(cplayer);
        /*
        while(getOption(cplayer) != 0){
            DO TURN
        }
        */

        if(isGameEnd(bang)){
            winner = isGameEnd(bang);
            break;
        }
        
        do {
            bang->_turn = (bang->_turn + 1) % bang->_total_player_cnt;
        }while(!isDead(&bang->_player[bang->_turn]));
    }
    return 1;
}
int32_t shuffingame[80] = {0};
void shuffle(game *bang)
{
    int32_t x = 0;
    for (int32_t i = bang->_discard_cnt-1; i >= 1; i--)
    {
        int32_t tempt = 0;
        // printf("%d\n", i);
        x = rand() % (i);
        tempt = shuffingame[i];
        shuffingame[i] = shuffingame[x];
        shuffingame[x] = tempt;
        bang->_deck[i] = bang->_discard[shuffingame[i]];
    }
    // printf("ok?\n");
    bang->_deck[0] = bang->_discard[shuffingame[0]];
    bang->_deck_cnt = bang->_discard_cnt;
    bang->_discard_cnt = 0;
    return;
}
void displayPlayer(const player *p)
{
    printf("Player %d info: \n", p->_id);
    printf("position: %d\n ", p->_position);
    printf("role name: %s\n", p->_role->_name);
    printf("role skill: %s\n", p->_role->_skill);
    printf("identity: %s\n", p->_identity);
    printf("hp: %d/%d\n", p->_hp,p->_max_hp);
    displayHandCard(p);
    if(p->_gun!=NULL)
    {
        printf("%s: %s\n", p->_gun->_name, p->_gun->_skill);
    }
    if(p->_horse!=NULL)
    {
        printf("%s: %s\n", p->_horse->_name, p->_horse->_skill);
    }
    if(p->_jail!=NULL)
    {
        printf("%s: %s\n", p->_jail->_name, p->_jail->_skill);
    }
    if(p->_dinamite!=NULL)
    {
        printf("%s: %s\n", p->_dinamite->_name, p->_dinamite->_skill);
    }
    if(p->_barrel!=NULL)
    {
        printf("%s: %s\n", p->_barrel->_name, p->_barrel->_skill);
    }
    return;
}
void displayHandCard(const player *p)
{
    printf("handcards: \n");
    for(int32_t i = 0; i<p->_hand_cnt; i++)
    {
        printf("%d: \n", i+1);
        printf("%s\n", p->_hand[i]->_name);
        printf("%s\n", p->_hand[i]->_skill);
    }
    return;
}
// write in card.c xxx
void displayAction(const player *p, card *c)
{
    printf("Player %d used %s\n", p->_id,c->_name);
    return;
}
bool judge(player*p,card *c, game* game)//判定
{
    if(strncmp("BARREL",c->_name,6)==0)
    {
        draw(p,game);
        if(p->_hand[p->_hand_cnt-1]->_suit==2)
        {
            discard(p,c,1,game);
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return true;
        }
        else
        {
            discard(p,c,1,game);
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return false;
        }
    }
    else if(strncmp("PRIGIONE",c->_name,8)==0)
    {
        draw(p,game);
        if(p->_hand[p->_hand_cnt-1]->_suit==2)
        {
            discard(p,c,1,game);
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return true;
        }
        else
        {
            discard(p,c,1,game);
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return false;
        }
    }
    else if(strncmp("DINAMITE",c->_name,8)==0)
    {
        draw(p,game);
        if(p->_hand[p->_hand_cnt-1]->_suit==1 && (p->_hand[p->_hand_cnt-1]->_number>=2 && p->_hand[p->_hand_cnt-1]->_number<=9))
        {
            discard(p,c,1,game);
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return true;
        }
        else
        {
            if(p->_position+1>game->_total_player_cnt)
            {
                game->_player[0]._dinamite = c;
                p->_dinamite = NULL;
            }
            else
            {
                (p+1)->_dinamite = c;
                p->_dinamite = NULL;
            }
            discard(p,p->_hand[p->_hand_cnt-1],2,game);
            return false;
        }
    }
    else
    {
        return false;
    }
return true;
}