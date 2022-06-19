#include "card.h"
// #include "player.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// after change hp isDead ? here or main vv
char *bangAction(player *me, card *c, player *target, game *game)
{
    // // check target is me?
    // if(target->_id == me->_id)
    // {
    //     return displayAction(me, c, 4);
    // }
    // check distance
    int32_t changeDistance = 0;
    int32_t betweenDistance = 0;
    int32_t availDistance = 1;
    checkDistance(&betweenDistance, &changeDistance, me, target, game);
    // printf("check distance\n");
    if (me->_gun != NULL)
    {
        if (strncmp("VOLCANIC", me->_gun->_name, 8) == 0)
        {
            availDistance = 1;
        }
        else if (strncmp("SCHOFIELD", me->_gun->_name, 9) == 0)
        {
            availDistance = 2;
        }
        else if (strncmp("REMINGTON", me->_gun->_name, 9) == 0)
        {
            availDistance = 3;
        }
        else if (strncmp("REV. CARABINE", me->_gun->_name, 13) == 0)
        {
            availDistance = 4;
        }
        else if (strncmp("WINCHESTER", me->_gun->_name, 10) == 0)
        {
            availDistance = 5;
        }
    }
    // printf("check gun\n");
    // check card is bang or other
    if (strncmp("BANG", c->_name, 4) == 0 ||
        (strncmp("MANCATO", c->_name, 7) == 0 && strncmp("CalamityJanet", me->_role->_name, 13) == 0))
    {
        if (betweenDistance <= availDistance)
        {

            // throw a card
            // (*me)._hand_cnt -= 1;
            // (*me)._hand
            // printf("check used\n");
            discard(me, c, 2, game);
            // changeHp
            changeHP(target, -1, game);
            if (strncmp(target->_role->_name, "ElGringo", 8) == 0)
            {
                printf("Since Player %s is ElGringo, he can draw your card\n", target->_name);
                drawplayer(target, me, 2);
            }
            return displayAction(me, c, 3);
        }
        else
        {
            // printf("fail\n");
            return displayAction(me, c, 4);
        }
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 4);
}
char *panic(player *me, card *c, player *target, game *game)
{
    // // check target is me?
    // if(target->_id == me->_id)
    // {
    //     return displayAction(me, c, 4);
    // }
    // check distance
    int32_t changeDistance = 0;
    int32_t betweenDistance = 0;
    checkDistance(&betweenDistance, &changeDistance, me, target, game);
    // handcardcnt
    if (target->_hand_cnt == 0)
    {
        return displayAction(me, c, 4);
    }
    // check card is panic or other
    if (strncmp("PANICOI", c->_name, 7) == 0)
    {
        if (betweenDistance <= 1)
        {
            // draw (not computer)
            if (me->_id == 0)
            {
                while (1)
                {
                    int32_t choose = 0;
                    printf("You can draw a card from Player %s\n", target->_name);
                    printf("What do you want to draw?\n");
                    printf("1: Equipments\n2: Hand cards\n3: Cancel\nYour choice: ");
                    scanf("%d", &choose);
                    fflush(stdin);
                    if (choose == 1)
                    {
                        if (drawplayer(me, target, 1) == false)
                        {
                            printf("He/She didn't have equipment cards!\n");
                            return displayAction(me, c, 4);
                        }
                        else
                        {
                            printf("Draw success!\n");
                            break;
                        }
                    }
                    else if (choose == 2)
                    {
                        if (drawplayer(me, target, 2) == false)
                        {
                            printf("He/She didn't have hand cards!\n");
                            return displayAction(me, c, 4);
                        }
                        else
                        {
                            printf("Draw success!\n");
                            break;
                        }
                    }
                    else if (choose == 3)
                    {
                        printf("You didn't use this card.\n");
                        return displayAction(me, c, 4);
                    }
                    else
                    {
                        printf("Your input has problem, please try again.\n");
                    }
                }
            }
            // computer xxx
            else
            {
                if (drawplayer(me, target, 2) == false)
                {
                    printf("He/She didn't have hand cards!\n");
                    return displayAction(me, c, 4);
                }
                else
                {
                    printf("Draw success!\n");
                }
            }
            // throw a card
            discard(me, c, 2, game);
            return displayAction(me, c, 3);
        }
        else
        {
            return displayAction(me, c, 4);
        }
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}
char *catBalou(player *me, card *c, player *target, game *game)
{
    // // check target is me?
    // if(target->_id == me->_id)
    // {
    //     return displayAction(me, c, 4);
    // }
    // check card is catBalou or other
    if (strncmp("CATBALOU", c->_name, 8) == 0)
    {
        if (target->_hand_cnt == 0 && target->_gun == NULL && target->_horse == NULL && target->_jail == NULL && target->_dinamite == NULL && target->_barrel == NULL)
        {
            printf("Target don't have cards!\n");
            return displayAction(me, c, 4);
        }
        if (target->_id == 0)
        {
            while (1)
            {
                int32_t choose = 0;
                printf("You need to throw a card!\n");
                printf("What do you want to throw?\n");
                printf("1: Equipments\n2: Hand cards\nYour choice: ");
                scanf("%d", &choose);
                fflush(stdin);
                if (choose == 1)
                {
                    if (throwaway(me, target, 1, game) == false)
                    {
                        printf("You didn't have equipment cards!\n");
                    }
                    else
                    {
                        printf("Throw success!\n");
                        break;
                    }
                }
                else if (choose == 2)
                {
                    if (throwaway(me, target, 2, game) == false)
                    {
                        printf("You didn't have hand cards!\n");
                    }
                    else
                    {
                        printf("Throw success!\n");
                        break;
                    }
                }
                else
                {
                    printf("Your input is wrong. Please try again.\n");
                }
            }
        }
        // computer player
        else
        {
            if (target->_hand_cnt != 0)
            {
                // printf("discard\n");
                discard(target, target->_hand[target->_hand_cnt - 1], 2, game);
                // printf("discard success\n");
            }
            else
            {
                if (target->_dinamite != NULL)
                {
                    discard(target, target->_dinamite, 1, game);
                    target->_dinamite = NULL;
                }
                else if (target->_jail != NULL)
                {
                    discard(target, target->_jail, 1, game);
                    target->_jail = NULL;
                }
                else if (target->_horse != NULL)
                {
                    discard(target, target->_horse, 1, game);
                    target->_horse = NULL;
                }
                else if (target->_gun != NULL)
                {
                    discard(target, target->_gun, 1, game);
                    target->_gun = NULL;
                }
                else if (target->_barrel != NULL)
                {
                    discard(target, target->_barrel, 1, game);
                    target->_barrel = NULL;
                }
            }
        }
        discard(me, c, 2, game);
        // printf("discard me\n");
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}

char *duel(player *me, card *c, player *target, game *game)
{
    // // check target is me?
    // if(target->_id == me->_id)
    // {
    //     return displayAction(me, c, 4);
    // }
    player *temptplayer = NULL;
    int32_t end = 0;
    for (int32_t i = 1; i >= 0; i++)
    {
        if (i % 2 == 1)
        {
            temptplayer = target;
        }
        else
        {
            temptplayer = me;
        }
        if (temptplayer->_id == 0)
        {
            int32_t choose = 0;
            printf("Do you want to throw bang?\n");
            printf("1: Yes\n2: No\nChoice: ");
            scanf("%d", &choose);
            fflush(stdin);
            if (choose == 1)
            {
                if(temptplayer->_hand_cnt == 0)
                {
                    printf("But you don't have \"BANG\"cards to throw.\n");
                    printf("So you will lose one life.\n");
                    end = 1;                    
                }
                for (int32_t j = 0; j < temptplayer->_hand_cnt; j++)
                {
                    if (strncmp("CalamityJanet", temptplayer->_role->_name, 4) == 0)
                    {
                        if (strncmp("BANG", temptplayer->_hand[j]->_name, 4) == 0 || strncmp("MANCATO", temptplayer->_hand[j]->_name, 7) == 0)
                        {
                            discard(temptplayer, temptplayer->_hand[j], 2, game);
                            break;
                        }
                    }
                    else
                    {
                        if (strncmp("BANG", temptplayer->_hand[j]->_name, 4) == 0)
                        {
                            discard(temptplayer, temptplayer->_hand[j], 2, game);
                            break;
                        }
                    }
                    if (j == temptplayer->_hand_cnt - 1)
                    {
                        printf("But you don't have \"BANG\"cards to throw.\n");
                        printf("So you will lose one life.\n");
                        end = 1;
                        break;
                    }
                }
            }
            else if (choose == 2)
            {
                printf("Ok. But you need to lose one life.\n");
                end = 1;
            }
            else
            {
                printf("Wrong input. Please try again.\n");
            }
        }
        else
        {
            if(temptplayer->_hand_cnt == 0)
            {
                end = 1;
            }
            for (int32_t j = 0; j < temptplayer->_hand_cnt; j++)
            {
                if (strncmp("CalamityJanet", temptplayer->_role->_name, 4) == 0)
                {
                    if (strncmp("BANG", temptplayer->_hand[j]->_name, 4) == 0 || strncmp("MANCATO", temptplayer->_hand[j]->_name, 7) == 0)
                    {
                        discard(temptplayer, temptplayer->_hand[j], 2, game);
                        break;
                    }
                }
                else
                {
                    if (strncmp("BANG", temptplayer->_hand[j]->_name, 4) == 0)
                    {
                        discard(temptplayer, temptplayer->_hand[j], 2, game);
                        break;
                    }
                }
                if (j == temptplayer->_hand_cnt - 1)
                {
                    end = 1;
                    break;
                }
            }
        }
        if (end == 1)
        {
            break;
        }
    }
    changeHP(temptplayer, -1, game);
    if (strncmp(temptplayer->_role->_name, "ElGringo", 8) == 0)
    {
        printf("Player %s is ElGringo, so %s can draw a card\n", target->_name, target->_name);
        if (temptplayer == me)
        {
            // printf("Start draw?\n");
            drawplayer(temptplayer, target, 2);
        }
        else
        {
            // printf("Start draw2?\n");
            drawplayer(temptplayer, me, 2);
        }
    }
    discard(me, c, 2, game);
    return displayAction(me, c, 3);
}

char *missed(player *me, card *c, game *game)
{
    // check if it is missed
    if (strncmp("MANCATO", c->_name, 7) == 0)
    {
        discard(me, c, 2, game);
        changeHP(me, 1, game);
        return displayAction(me, c, 3);
    }
    else if (strncmp("BANG", c->_name, 4) == 0 && strncmp("CalamityJanet", me->_role->_name, 13) == 0)
    {
        discard(me, c, 2, game);
        changeHP(me, 1, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }

    return displayAction(me, c, 3);
}
// fix draw function? vv
char *stageCoach(player *me, card *c, game *game)
{
    // check if it is draw two cards
    if (strncmp("DILIGENZA", c->_name, 9) == 0)
    {
        draw(me, game);
        draw(me, game);
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}
// fix draw function? vv
char *wellsFargo(player *me, card *c, game *game)
{
    // check if it is draw three cards
    if (strncmp("WELLSFARGO", c->_name, 10) == 0)
    {
        draw(me, game);
        draw(me, game);
        draw(me, game);
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}

char *beer(player *me, card *c, game *game)
{
    // check player num
    if (game->_alive_player_cnt <= 2)
    {
        return displayAction(me, c, 4);
    }
    // check if it is beer
    if (strncmp("BIRRA", c->_name, 5) == 0)
    {
        changeHP(me, 1, game);
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}
char *saloon(player *me, card *c, game *game)
{
    // check if it is saloon
    if (strncmp("SALOON", c->_name, 6) == 0)
    {
        for (int32_t i = 0; i < game->_total_player_cnt; i++)
        {
            if (isDead(game->_player[i]) == true)
            {
                continue;
            }
            else
            {
                changeHP(game->_player[i], 1, game);
            }
        }
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}
// fix draw func vv
// displayhandcard need number
char *generalStore(player *me, card *c, game *game)
{
    int32_t index = 0;
    player *temptplayer = me;
    player *temptplayer2 = calloc(1, sizeof(player));
    temptplayer2->_hand = calloc(10, sizeof(card *));
    // printf("init\n");
    for (int32_t i = 0; i < 10; i++)
    {
        temptplayer2->_hand[i] = calloc(1, sizeof(card));
    }
    // printf("init2\n");
    for (int32_t i = 0; i < game->_alive_player_cnt; i++)
    {
        draw(temptplayer2, game);
    }
    // printf("init3\n");
    int32_t next_man = game->_turn;
    do
    {
        if (temptplayer->_id == 0 )
        {
            while (1)
            {
                int32_t want = 0;
                displayHandCard(temptplayer2);
                printf("Which one do you choose: ");
                scanf("%d", &want);
                fflush(stdin);
                if (want >= 1 && want <= temptplayer2->_hand_cnt)
                {
                    // sort me
                    temptplayer->_hand_cnt += 1;
                    int32_t cnt = temptplayer->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    temptplayer->_hand[cnt - 1] = temptplayer2->_hand[want - 1];
                    // sort target
                    for (int32_t i = want - 1; i < temptplayer2->_hand_cnt; i++)
                    {
                        if (i == temptplayer2->_hand_cnt - 1)
                        {
                            // free(*(temptplayer2->_hand) + (want - 1));
                            break;
                        }
                        temptplayer2->_hand[i] = temptplayer2->_hand[i + 1];
                    }
                    temptplayer2->_hand_cnt -= 1;
                    // printf("break???\n");
                    break;
                }
                else
                {
                    printf("Your input is wrong. Please try again.\n");
                }
            }
        }
        else 
        {

            // sort temptplayer
            temptplayer->_hand_cnt += 1;
            int32_t cnt = temptplayer->_hand_cnt;
            // temptplayer->_hand[cnt - 1] = calloc(1, sizeof(card));
            temptplayer->_hand[cnt - 1] = temptplayer2->_hand[temptplayer2->_hand_cnt - 1];
            // sort target
            // free(*(temptplayer2->_hand) + (temptplayer2->_hand_cnt - 1));
            temptplayer2->_hand_cnt -= 1;
        }
        do {
            next_man = (next_man + 1) % game->_total_player_cnt;
        } while (isDead(game->_player[next_man]));
        // printf("break?\n");
        temptplayer = game->_player[next_man];
        if(temptplayer == me)
        {
            break;
        }
    } while (temptplayer != me);
    discard(me, c, 2, game);
    return displayAction(me, c, 3);
}
char *gatling(player *me, card *c, game *game)
{
    // check if it is gatling
    if (strncmp("GATLING", c->_name, 7) == 0)
    {
        for (int32_t i = 0; i < game->_total_player_cnt; i++)
        {
            if (isDead(game->_player[i]) == true)
            {
                continue;
            }
            else if (game->_player[i]->_id == me->_id)
            {
                continue;
            }
            else
            {
                changeHP(game->_player[i], -1, game);
                if (strncmp(game->_player[i]->_role->_name, "ElGringo", 8) == 0)
                {
                    printf("Player %s is ElGringo, so %s can draw a card\n", game->_player[i]->_name, game->_player[i]->_name);
                    // printf("gat start draw?\n");
                    drawplayer(game->_player[i], me, 2);
                }
            }
        }
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}
char *indians(player *me, card *c, game *game)
{
    // check if it is indians
    if (strncmp("INDIANI", c->_name, 7) == 0)
    {
        for (int32_t i = 0; i < game->_total_player_cnt; i++)
        {
            if (isDead(game->_player[i]) == true)
            {
                continue;
            }
            else if (game->_player[i]->_id == me->_id)
            {
                continue;
            }
            else
            {
                if(game->_player[i]->_hand_cnt == 0)
                {
                    changeHP(game->_player[i], -1, game);
                    if (strncmp(game->_player[i]->_role->_name, "ElGringo", 8) == 0)
                    {
                        printf("Because Player %s is ElGringo, so ElGringo can draw a card\n", game->_player[i]->_name);
                        drawplayer(game->_player[i], me, 2);
                    }                    
                }
                for (int32_t j = 0; j < game->_player[i]->_hand_cnt; j++)
                {
                    if (strncmp("CalamityJanet", game->_player[i]->_role->_name, 13) == 0)
                    {
                        if (strncmp("BANG", game->_player[i]->_hand[j]->_name, 4) == 0 || strncmp("MANCATO", game->_player[i]->_hand[j]->_name, 7) == 0)
                        {
                            discard(game->_player[i], game->_player[i]->_hand[j], 2, game);
                            break;
                        }
                        if (j == game->_player[i]->_hand_cnt - 1)
                        {
                            changeHP(game->_player[i], -1, game);
                            if (strncmp(game->_player[i]->_role->_name, "ElGringo", 8) == 0)
                            {
                                printf("Because Player %s is ElGringo, so ElGringo can draw a card\n", game->_player[i]->_name);
                                drawplayer(game->_player[i], me, 2);
                            }
                            break;
                        }
                    }
                    else
                    {
                        if (strncmp("BANG", game->_player[i]->_hand[j]->_name, 4) == 0)
                        {
                            discard(game->_player[i], game->_player[i]->_hand[j], 2, game);
                            break;
                        }
                        if (j == game->_player[i]->_hand_cnt - 1)
                        {
                            changeHP(game->_player[i], -1, game);
                            if (strncmp(game->_player[i]->_role->_name, "ElGringo", 8) == 0)
                            {
                                printf("Because Player %s is ElGringo, so ElGringo can draw a card\n", game->_player[i]->_name);
                                drawplayer(game->_player[i], me, 2);
                            }
                            break;
                        }
                    }
                }
            }
            if( i+1 == game->_total_player_cnt)
            {
                break;
            }
        }
        discard(me, c, 2, game);
        return displayAction(me, c, 3);
    }
    else
    {
        return displayAction(me, c, 4);
    }
    return displayAction(me, c, 3);
}

void checkDistance(int32_t *between, int32_t *cD, player *me, player *target, game *game)
{
    if (strncmp("RoseDoolan", me->_role->_name, 10) == 0)
    {
        *cD -= 1;
    }
    // printf("check NUll?\n");
    if (me->_horse != NULL)
    {
        // printf("inside\n");
        if (strncmp("APPALOOSA", me->_horse->_name, 9) == 0)
        {
            *cD -= 1;
        }
    }
    // printf("check NUll?\n");
    if (strncmp("PaulRegret", target->_role->_name, 10) == 0)
    {
        *cD += 1;
    }
    if (target->_horse != NULL)
    {
        if (strncmp("MUSTANG", target->_horse->_name, 7) == 0)
        {
            *cD += 1;
        }
    }
    *between = abs(me->_position - target->_position);
    if (game->_alive_player_cnt - *between < *between)
    {
        *between = game->_alive_player_cnt - *between;
    }
    *between += *cD;

    return;
}
// get info printf information? vv 1: equip 2: hand
bool drawplayer(player *me, player *target, int8_t choice)
{
    if (me->_id == 0)
    {
        if (choice == 1)
        {
            if (target->_gun == NULL && target->_horse == NULL && target->_jail == NULL && target->_dinamite == NULL && target->_barrel == NULL)
            {
                return false;
            }
            while (1)
            {
                int32_t index = 1;
                int32_t want = 0;
                if (target->_gun != NULL)
                {
                    printf("%d: \n", index);
                    getGunInfo(target);
                }
                index += 1;
                if (target->_horse != NULL)
                {
                    printf("%d: \n", index);
                    getHorseInfo(target);
                }
                index += 1;
                if (target->_jail != NULL)
                {
                    printf("%d: \n", index);
                    getJailInfo(target);
                }
                index += 1;
                if (target->_dinamite != NULL)
                {
                    printf("%d: \n", index);
                    getDinamiteInfo(target);
                }
                index += 1;
                if (target->_barrel != NULL)
                {
                    printf("%d: \n", index);
                    getBarrelInfo(target);
                }
                index += 1;
                printf("Which one do you want: ");
                scanf("%d", &want);
                fflush(stdin);
                if (want == 1 && target->_gun != NULL)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_gun;
                    // sort target
                    // card* tempt = calloc(1,sizeof(card*));            
                    // target->_gun = tempt;
                    target->_gun = NULL;
                    break;
                }
                else if (want == 2 && target->_horse != NULL)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_horse;
                    // sort target
                    // card* tempt = calloc(1,sizeof(card*));            
                    // target->_horse = tempt;
                    target->_horse = NULL;
                    break;
                }
                else if (want == 3 && target->_jail != NULL)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_jail;
                    // sort target
                    // card* tempt = calloc(1,sizeof(card*));            
                    // target->_jail = tempt;
                    target->_jail = NULL;
                    break;
                }
                else if (want == 4 && target->_dinamite != NULL)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_dinamite;
                    // sort target
                    // card* tempt = calloc(1,sizeof(card*));            
                    // target->_dinamite = tempt;
                    target->_dinamite = NULL;
                    break;
                }
                else if (want == 5 && target->_barrel != NULL)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_barrel;
                    // sort target
                    target->_barrel = NULL;
                    break;
                }
                else
                {
                    printf("Your input is wrong. Please try again.\n");
                }
            }
        }
        else if (choice == 2)
        {
            if (target->_hand_cnt == 0)
            {
                return false;
            }
            while (1)
            {
                int32_t want = 0;
                for (int32_t i = 1; i <= target->_hand_cnt; i++)
                {
                    printf("%d\n", i);
                }
                printf("Which one do you choose: ");
                scanf("%d", &want);
                fflush(stdin);
                if (want >= 1 && want <= target->_hand_cnt)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    // me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    me->_hand[cnt - 1] = target->_hand[want - 1];

                    // sort target
                    for (int32_t i = want - 1; i < target->_hand_cnt; i++)
                    {
                        if (i == target->_hand_cnt - 1)
                        {
                            // free(*(target->_hand) + (want - 1));
                            break;
                        }
                        target->_hand[i] = target->_hand[i + 1];
                    }
                    target->_hand_cnt -= 1;
                    break;
                }
                else
                {
                    printf("Your input is wrong. Please try again.\n");
                }
            }
            return true;
        }
    }
    else
    {
        if (target->_hand_cnt == 0 && target->_gun == NULL && target->_horse == NULL && target->_dinamite == NULL && target->_jail == NULL && target->_barrel == NULL)
        {
            return false;
        }
        if(choice == 2)
        {
            // sort me
            me->_hand_cnt += 1;
            int32_t cnt = me->_hand_cnt;
            // me->_hand[cnt - 1] = calloc(1, sizeof(card));
            me->_hand[cnt - 1] = target->_hand[target->_hand_cnt - 1];
            // sort target

            // free(*(target->_hand) + (target->_hand_cnt - 1));

            target->_hand_cnt -= 1;
        }
        else if(choice == 1)
        {
            me->_hand_cnt += 1;
            int32_t cnt = me->_hand_cnt;   
            if (target->_gun != NULL)
            {
                card *c = target->_gun;
                me->_hand[cnt - 1] = c;  
                card* tempt = calloc(1,sizeof(card*));            
                target->_gun = tempt;
                target->_gun = NULL;
            }
            if (target->_horse!= NULL)
            {
                card *c = target->_horse;
                me->_hand[cnt - 1] = c;  
                card* tempt = calloc(1,sizeof(card*));            
                target->_horse = tempt;
                target->_horse = NULL;
            }  
            if (target->_dinamite!= NULL)
            {
                card *c = target->_dinamite;
                me->_hand[cnt - 1] = c;  
                card* tempt = calloc(1,sizeof(card*));            
                target->_dinamite= tempt;
                target->_dinamite = NULL;
            }   
            if (target->_jail!= NULL)
            {
                card *c = target->_jail;
                me->_hand[cnt - 1] = c;  
                card* tempt = calloc(1,sizeof(card*));            
                target->_jail = tempt;
                target->_jail = NULL;
            } 
            if (target->_barrel!= NULL)
            {
                card *c = target->_barrel;
                me->_hand[cnt - 1] = c;  
                card* tempt = calloc(1,sizeof(card*));            
                target->_barrel = tempt;
                target->_barrel = NULL;
            }                          
        }
        return true;
    }
    return true;
}

bool throwaway(player *me, player *target, int8_t choice, game *game)
{
    if (choice == 1)
    {
        if (target->_gun == NULL && target->_horse == NULL && target->_jail == NULL && target->_dinamite == NULL && target->_barrel == NULL)
        {
            return false;
        }
        while (1)
        {
            int32_t index = 1;
            int32_t want = 0;
            if (target->_gun != NULL)
            {
                printf("%d: \n", index);
                getGunInfo(target);
            }
            index += 1;
            if (target->_horse != NULL)
            {
                printf("%d: \n", index);
                getHorseInfo(target);
            }
            index += 1;
            if (target->_jail != NULL)
            {
                printf("%d: \n", index);
                getJailInfo(target);
            }
            index += 1;
            if (target->_dinamite != NULL)
            {
                printf("%d: \n", index);
                getDinamiteInfo(target);
            }
            index += 1;
            if (target->_barrel != NULL)
            {
                printf("%d: \n", index);
                getBarrelInfo(target);
            }
            index += 1;
            printf("Which one do you want to throw: ");
            scanf("%d", &want);
            fflush(stdin);
            if (want == 1 && target->_gun != NULL)
            {
                // sort target
                discard(target, target->_gun, 1, game);
                target->_gun = NULL;
                break;
            }
            else if (want == 2 && target->_horse != NULL)
            {
                // sort target
                discard(target, target->_horse, 1, game);
                target->_horse = NULL;
                break;
            }
            else if (want == 3 && target->_jail != NULL)
            {
                // sort target
                discard(target, target->_jail, 1, game);
                target->_jail = NULL;
                break;
            }
            else if (want == 4 && target->_dinamite != NULL)
            {
                // sort target
                discard(target, target->_dinamite, 1, game);
                target->_dinamite = NULL;
                break;
            }
            else if (want == 5 && target->_barrel != NULL)
            {
                // sort target
                discard(target, target->_barrel, 1, game);
                target->_barrel = NULL;
                break;
            }
            else
            {
                printf("Your input is wrong. Please try again.\n");
            }
        }
    }
    else if (choice == 2)
    {
        if (target->_hand_cnt == 0)
        {
            return false;
        }
        while (1)
        {
            int32_t want = 0;
            displayHandCard(target);
            printf("Which one do you want to throw: ");
            scanf("%d", &want);
            fflush(stdin);
            if (want >= 1 && want <= target->_hand_cnt)
            {
                // sort target
                discard(target, target->_hand[want - 1], 2, game);
                for (int32_t i = want - 1; i < target->_hand_cnt; i++)
                {
                    if (i == target->_hand_cnt - 1)
                    {
                        // free(*(target->_hand) + (want - 1));
                        break;
                    }
                    target->_hand[i] =target->_hand[i + 1];
                }
                target->_hand_cnt -= 1;
                break;
            }
            else
            {
                printf("Your input is wrong. Please try again.\n");
            }
        }
        return true;
    }

    return true;
}