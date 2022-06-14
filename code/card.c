#include "card.h"
// #include "player.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void deckInit(game *game)
{
    srand(time(NULL));
    int32_t shuff[80] = {0};
    int32_t x = 0;
    game->_discard = calloc(80, sizeof(card *));
    game->_deck = calloc(80, sizeof(card *));
    for (int32_t i = 0; i < 80; i++)
    {
        game->_discard[i] = calloc(1, sizeof(card));
        game->_deck[i] = calloc(1, sizeof(card));
        shuff[i] = i + 1;
    }
    for (int32_t i = 79; i >= 1; i++)
    {
        int32_t tempt = 0;
        x = rand() % (i);
        tempt = shuff[i];
        shuff[i] = shuff[x];
        shuff[x] = tempt;
        game->_deck[i] = (card *)(CARD[shuff[i]]);
    }
    game->_deck[0] = (card *)(CARD[shuff[0]]);
    return;
}

// after change hp isDead ? here or main
bool bang(player *me, card *c, player *target, game *game)
{
    // check distance
    int32_t changeDistance = 0;
    int32_t betweenDistance = 0;
    int32_t availDistance = 1;
    checkDistance(&betweenDistance, &changeDistance, me, target, game);
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
    // check card is bang or other
    if (strncmp("BANG", c->_name, 4) == 0)
    {
        if (betweenDistance <= availDistance)
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
        if (betweenDistance <= availDistance)
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
bool catBalou(player *me, card *c, player *target)
{
    // check card is carBalou or other
    if (strncmp("CATBALOU", c->_name, 8) == 0)
    {
        if (target->_hand_cnt == 0 && target->_gun == NULL && target->_horse == NULL && target->_jail == NULL && target->_dinamite == NULL && target->_barrel == NULL)
        {
            printf("Target don't have cards!\n");
            return false;
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
                if (choose == 1)
                {
                    if (throwaway(me, target, 1) == false)
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
                    if (throwaway(me, target, 2) == false)
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
                discard(target, (*(target->_hand) + (target->_hand_cnt - 1)));
            }
            else
            {
                if (target->_dinamite != NULL)
                {
                    discard(target, target->_dinamite);
                }
                else if (target->_jail != NULL)
                {
                    discard(target, target->_jail);
                }
                else if (target->_horse != NULL)
                {
                    discard(target, target->_horse);
                }
                else if (target->_gun != NULL)
                {
                    discard(target, target->_gun);
                }
                else if (target->_barrel != NULL)
                {
                    discard(target, target->_barrel);
                }
            }
        }
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
// temptly put
bool duel(player *me, card *c, player *target, game *game)
{

    return true;
}

bool missed(player *me, card *c)
{
    // check if it is missed
    if (strncmp("MANCATO", c->_name, 7) == 0)
    {
        discard(me, c);
        return true;
    }
    else if (strncmp("BANG", c->_name, 4) == 0 && strncmp("CalamityJanet", me->_role->_name, 13) == 0)
    {
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }

    return true;
}
// fix draw function?
bool stageCoach(player *me, card *c)
{
    // check if it is draw two cards
    if (strncmp("DILIGENZA", c->_name, 9) == 0)
    {
        draw(me, NULL);
        draw(me, NULL);
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
// fix draw function?
bool wellsFargo(player *me, card *c)
{
    // check if it is draw three cards
    if (strncmp("WELLSFARGO", c->_name, 10) == 0)
    {
        draw(me, NULL);
        draw(me, NULL);
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}

bool beer(player *me, card *c, game *game)
{
    // check player num
    if (game->_alive_player_cnt <= 2)
    {
        return false;
    }
    // check if it is beer
    if (strncmp("BIRRA", c->_name, 5) == 0)
    {
        changeHP(me, 1);
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
bool saloon(player *me, card *c, game *game)
{
    // check if it is saloon
    if (strncmp("SALOON", c->_name, 6) == 0)
    {
        for (int32_t i = 0; i < game->_total_player_cnt; i++)
        {
            if (isDead(&(game->_player[i])) == true)
            {
                continue;
            }
            else
            {
                changeHP(&(game->_player[i]), 1);
            }
        }
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
// fix draw func
// displayhandcard need number
bool generalStore(player *me, card *c, game *game)
{
    int32_t index = 0;
    player *temptplayer = me;
    player *temptplayer2 = calloc(1, sizeof(player));
    temptplayer2->_hand = calloc(10, sizeof(card *));
    for (int32_t i = 0; i < 10; i++)
    {
        temptplayer2->_hand[i] = calloc(1, sizeof(card));
    }
    for (int32_t i = 0; i < game->_alive_player_cnt; i++)
    {
        draw(temptplayer2, NULL);
    }
    do
    {
        if (temptplayer == me)
        {
            while (1)
            {
                int32_t want = 0;
                displayHandCard(temptplayer2);
                printf("Which one do you choose: ");
                scanf("%d", &want);
                if (want >= 1 && want <= temptplayer2->_hand_cnt)
                {
                    // sort me
                    me->_hand_cnt += 1;
                    int32_t cnt = me->_hand_cnt;
                    me->_hand[cnt - 1] = calloc(1, sizeof(card));
                    *(*(me->_hand) + (cnt - 1)) = *(*(temptplayer2->_hand) + (want - 1));
                    // sort target
                    for (int32_t i = want - 1; i < temptplayer2->_hand_cnt; i++)
                    {
                        if (i == temptplayer2->_hand_cnt - 1)
                        {
                            free(*(temptplayer2->_hand) + (want - 1));
                            break;
                        }
                        *(*(temptplayer2->_hand) + (i)) = *(*(temptplayer2->_hand) + (i + 1));
                    }
                    temptplayer2->_hand_cnt -= 1;
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
            temptplayer->_hand[cnt - 1] = calloc(1, sizeof(card));
            *(*(temptplayer->_hand) + (cnt - 1)) = *(*(temptplayer2->_hand) + (temptplayer2->_hand_cnt - 1));
            // sort target
            free(*(temptplayer2->_hand) + (temptplayer2->_hand_cnt - 1));
            temptplayer2->_hand_cnt -= 1;
        }
        if (temptplayer->_position == game->_alive_player_cnt)
        {
            temptplayer = &game->_player[0];
        }
        else
        {
            temptplayer += 1;
        }
    } while (temptplayer != me);

    return true;
}
bool gatling(player *me, card *c, game *game)
{
    // check if it is gatling
    if (strncmp("GATLING", c->_name, 7) == 0)
    {
        for (int32_t i = 0; i < game->_total_player_cnt; i++)
        {
            if (isDead(&(game->_player[i])) == true)
            {
                continue;
            }
            else if (game->_player[i]._id == me->_id)
            {
                continue;
            }
            else
            {
                changeHP(&(game->_player[i]), -1);
            }
        }
        discard(me, c);
        return true;
    }
    else
    {
        return false;
    }
    return true;
}
bool indians(player *me, card *c, game *game)
{

    return true;
}

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
                printf("%d\n", i);
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

bool throwaway(player *me, player *target, int8_t choice)
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
            printf("Which one do you want to throw: ");
            scanf("%d", &want);
            if (want == 1 && target->_gun != NULL)
            {
                // sort target
                discard(target, target->_gun);
                break;
            }
            else if (want == 2 && target->_horse != NULL)
            {
                // sort target
                discard(target, target->_horse);
                break;
            }
            else if (want == 3 && target->_jail != NULL)
            {
                // sort target
                discard(target, target->_jail);
                break;
            }
            else if (want == 4 && target->_dinamite != NULL)
            {
                // sort target
                discard(target, target->_dinamite);
                break;
            }
            else if (want == 5 && target->_barrel != NULL)
            {
                // sort target
                discard(target, target->_barrel);
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
            displayHandCard(target);
            printf("Which one do you want to throw: ");
            scanf("%d", &want);
            if (want >= 1 && want <= target->_hand_cnt)
            {
                // sort target
                discard(target, (*(target->_hand) + (want - 1)));
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
