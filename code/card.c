#include "card.h"
// #include "player.h"
#include <math.h>
#include <stdlib.h>

card *deckInit(card **discard)
{
    card *tempt;
    return tempt;
}

// after change hp isDead ? here or main
bool bang(player *me, card *c, player *target, game *game)
{
    // check distance
    int32_t changeDistance = 0;
    int32_t betweenDistance = 0;
    checkDistance(&betweenDistance, &changeDistance, me, target, game);
    // check card is bang or other
    if (strncmp("BANG", c->_name, 4) == 0)
    {
        if (betweenDistance <= 1)
        {

            // throw a card
            // (*me)._hand_cnt -= 1;
            // (*me)._hand
            discard(me, c);
            // changeHp
            changeHP(target, -1);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (strncmp("MANCATO", c->_name, 7) == 0 && strncmp("CalamityJanet", me->_role->_name, 13) == 0)
    {
        if (betweenDistance <= 1)
        {
            // throw a card
            discard(me, c);
            // changeHp
            changeHP(target, -1);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
bool panic(player *me, card *c, player *target, game *game)
{
    // check distance
    int32_t changeDistance = 0;
    int32_t betweenDistance = 0;
    checkDistance(&betweenDistance, &changeDistance, me, target, game);
    // check card is panic or other
    if (strncmp("PANICOI", c->_name, 7) == 0)
    {
        if (betweenDistance <= 1)
        {
            // draw
            while (1)
            {
                int32_t choose = 0;
                printf("You can draw a card from Player %d\n", target->_id);
                printf("What do you want to draw?\n");
                printf("1: Equipments\n2: Hand cards\n3: Cancle\nYour choice: ");
                scanf("%d", &choose);
                if (choose == 1)
                {
                    if (drawplayer(me, target, 1) == false)
                    {
                        printf("He/She didn't have equipment cards!\n");
                        return false;
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
                        return false;
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
                    return false;
                }
                else
                {
                    printf("Your input has problem, please try again.\n");
                }
            }
            // throw a card
            discard(me, c);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
bool catBalou(player *me, card *c, player *target, game *game)
{
    return true;
}
bool duel(player *me, card *c, player *target, game *game)
{
    return true;
}

bool missed(player *me, card *c)
{
    return true;
}
bool beer(player *me, card *c)
{
    return true;
}
bool saloon(player *me, card *c)
{
    return true;
}
bool stageCoach(player *me, card *c)
{
    return true;
}
bool wellsFargo(player *me, card *c)
{
    return true;
}

bool generalStore(player *me, card *c, game *game);
bool gatling(player *me, card *c, game *game);
bool indians(player *me, card *c, game *game);

void checkDistance(int32_t *between, int32_t *cD, player *me, player *target, game *game)
{
    if (strncmp("RoseDoolan", me->_role->_name, 10) == 0)
    {
        *cD -= 1;
    }
    if (strncmp("APPALOOSA", me->_horse->_name, 9) == 0)
    {
        *cD -= 1;
    }
    if (strncmp("PaulRegret", target->_role->_name, 10) == 0)
    {
        *cD += 1;
    }
    if (strncmp("MUSTANG", target->_horse->_name, 7) == 0)
    {
        *cD += 1;
    }
    *between = abs(me->_position - target->_position);
    if (game->_alive_player_cnt - *between < *between)
    {
        *between = game->_alive_player_cnt - *between;
    }
    *between += *cD;

    return;
}
// get info printf information?
bool drawplayer(player *me, player *target, int8_t choice)
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
                getHourseInfo(target);
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
            if (want == 1 && target->_gun != NULL)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(target->_gun);
                // sort target
                free(target->_gun);
                target->_gun = NULL;
                break;
            }
            else if (want == 2 && target->_horse != NULL)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(target->_horse);
                // sort target
                free(target->_horse);
                target->_horse = NULL;
                break;
            }
            else if (want == 3 && target->_jail != NULL)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(target->_jail);
                // sort target
                free(target->_jail);
                target->_jail = NULL;
                break;
            }
            else if (want == 4 && target->_dinamite != NULL)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(target->_dinamite);
                // sort target
                free(target->_dinamite);
                target->_dinamite = NULL;
                break;
            }
            else if (want == 5 && target->_barrel != NULL)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(target->_barrel);
                // sort target
                target->_barrel = NULL;
                free(target->_barrel);
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
        if (target->_hand == NULL)
        {
            return false;
        }
        while (1)
        {
            int32_t want = 0;
            for (int32_t i = 1; i <= target->_hand_cnt; i++)
            {
                printf("%d: \n", i);
            }
            printf("Which one do you choose: ");
            scanf("%d", &want);
            if (want >= 1 && want <= target->_hand_cnt)
            {
                // sort me
                me->_hand_cnt += 1;
                int32_t cnt = me->_hand_cnt;
                me->_hand[cnt - 1] = calloc(1, sizeof(card));
                *(*(me->_hand) + (cnt - 1)) = *(*(target->_hand) + (want - 1));
                // sort target
                for (int32_t i = want - 1; i < target->_hand_cnt; i++)
                {
                    if (i == target->_hand_cnt - 1)
                    {
                        free(*(target->_hand) + (want - 1));
                        break;
                    }
                    *(*(target->_hand) + (i)) = *(*(target->_hand) + (i + 1));
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
// int main()
// {
//     card test = CARD_02;
//     card test2 = CARD_03;
//     player p1;
//     **p1._hand = test;
//     printf("%s\n", (**p1._hand)._name);
//     *(*p1._hand + 1) = test2;
//     // for (int32_t i = 0; i < 2; i++)
//     // {
//     //     printf("%s\n", *((*p1._hand) + i)._name);
//     // }
//     return 0;
// }
