#include "game.h"
#include <math.h>
#include <stdlib.h>

void saveLog(game *bang, char *message)
{
    char *fname = bang->_logfile_name;
    FILE *f;
    if ((f = fopen(fname, "a")) == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    fprintf(f, "%s\n", message);
    fclose(f);
}

char *isGameEnd(const game *bang)
{
    bool Sceriffo = false;
    bool Fuorilecce = false;
    bool Rinnecato = false;
    for (int i = 0; i < bang->_total_player_cnt; ++i)
    {
        if (isDead(bang->_player[i]))
            continue;
        //"Sceriffo", "Fuorilecce", "Fuorilecce", "Rinnecato", "Vice", "Fuorilecce", "Vice"
        switch (bang->_player[i]->_identity[0])
        {
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

    if (Sceriffo && !Fuorilecce && !Rinnecato)
    {
        return "Sceriffo camp";
    }
    else if (!Sceriffo && Fuorilecce && !Rinnecato)
    {
        return "Fuorilecce camp";
    }
    else if (!Sceriffo && !Fuorilecce && Rinnecato)
    {
        return "Rinnecato";
    }
    return NULL;
}

char *gameloop(game *bang)
{
    int32_t total_turn = 0;
    char *winner = "Nobody";
    while (total_turn <= 10 && total_turn >= 0)
    {
        ++total_turn;
        player *cplayer = bang->_player[bang->_turn]; // current player

        printf("\nTurn " YEL "%d" RESET ":", total_turn);
        for (int i = 0; i < bang->_alive_player_cnt; ++i)
        {
            if (bang->_player[i]->_position == cplayer->_position)
                printf(BLU " %s(YOU)" RESET, bang->_player[i]->_name);
            else
                printf(" %s", bang->_player[i]->_name);
        }
        printf("\n");
        // Judge Dynamite
        if (cplayer->_dinamite != NULL)
        {
            printf("You have a Dynamite, judging...\n");
            saveLog(bang, judge(cplayer, cplayer->_dinamite, bang));
        }
        // use beer to recover
        while (isDead(cplayer))
        {
            printf("You are almost dead (HP: %d/%d), finding BIRRA...\n", cplayer->_hp, cplayer->_max_hp);
            int32_t bear_cnt = 0;
            for (int i = 0; i < cplayer->_hand_cnt; ++i)
            {
                if (strncmp("BIRRA", cplayer->_hand[i]->_name, 5) == 0)
                {
                    ++bear_cnt;
                    printf("BIRRA found. using...\n");
                    saveLog(bang, beer(cplayer, cplayer->_hand[i], bang));
                }
            }
            if (bear_cnt == 0)
            {
                printf("No BIRRA, You are dead.\n");
                break;
            }
        }
        if (isDead(cplayer))
        {
            continue;
        }
        // Judge Jail
        if (cplayer->_jail != NULL)
        {
            printf("You are in a jail, judging...\n");
            char *m = judge(cplayer, cplayer->_jail, bang);
            saveLog(bang, m);
            if (m[0] == 'F')
            {
                printf("Stay in jail for one turn.\n");
                continue;
            }
        }

        // get 2 card;
        saveLog(bang, draw(cplayer, bang));
        saveLog(bang, draw(cplayer, bang));

        displayPlayer(cplayer);

        while (!isDead(cplayer))
        {
            int32_t opt = -1;
            int32_t action = -1;
            while (opt == -1)
            {
                opt = getOption(bang, cplayer);
                if (opt > cplayer->_hand_cnt)
                {
                    printf("No card selected. tryagain.");
                }
                /*
                while(action == -1){
                    action = getAction(bang, cplayer->_hand[opt-1]);
                }
                */
            }
            if (opt == 0)
            {
                break;
            }
        }

        if (isGameEnd(bang))
        {
            winner = isGameEnd(bang);
            break;
        }

        printf("Turn %d end.\n", total_turn);

        do
        {
            bang->_turn = (bang->_turn + 1) % bang->_total_player_cnt;
        } while (isDead(bang->_player[bang->_turn]));
    }
    return winner;
}
/*
need to check
    if (strncmp(cplayer->_role->_name, "BlackJack", 9) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "BartCassidy", 11) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "ElGringo", 8) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "JesseJones", 10) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "KitCarlson", 10) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "PedroRamirez", 12) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "SidKetchum", 12) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "SlabTheKiller", 13) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "VultureSam", 10) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "WillyTheKid", 11) == 0)
    {
    }
*/
int32_t getOption(game *bang, player *p)
{
    printf("---------------------\n");
    printf("0: End turn.\n");
    displayHandCard(p);
    printf("---------------------\nYour Choice " YEL "> " RESET);
    int32_t want = 0;
    scanf("%d", &want);
    return want;
}

int32_t getAction(game *bang, card *c)
{

    if (c->_skill[0] == 'E')
    { // Equipment
    }
    else if (c->_skill[0] == 'A')
    { // Action
    }
}

int32_t shuffingame[80] = {0};
void shuffle(game *bang)
{
    int32_t x = 0;
    for (int32_t i = bang->_discard_cnt - 1; i >= 1; i--)
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
    printf("Health    : %d/%d\n", p->_hp, p->_max_hp);
    printf("position  : %d\n", p->_position);
    printf("identity  : %s\n", (p->_id == 0 ? p->_identity : "TOP SECRET"));
    printf("role name : %s\n", p->_role->_name);
    printf("role skill: %s\n", p->_role->_skill);
    if (p->_gun != NULL)
    {
        printf("%s: %s\n", p->_gun->_name, p->_gun->_skill);
    }
    if (p->_horse != NULL)
    {
        printf("%s: %s\n", p->_horse->_name, p->_horse->_skill);
    }
    if (p->_jail != NULL)
    {
        printf("%s: %s\n", p->_jail->_name, p->_jail->_skill);
    }
    if (p->_dinamite != NULL)
    {
        printf("%s: %s\n", p->_dinamite->_name, p->_dinamite->_skill);
    }
    if (p->_barrel != NULL)
    {
        printf("%s: %s\n", p->_barrel->_name, p->_barrel->_skill);
    }
    return;
}
void displayHandCard(const player *p)
{
    // printf("handcards: \n");
    for (int32_t i = 0; i < p->_hand_cnt; i++)
    {
        printf("%d: ", i + 1);
        printf("%s\n", p->_hand[i]->_name);
        // printf("%s\n", p->_hand[i]->_skill);
    }
    return;
}
// write in card.c vv
char strmessage[200] = {0};
char *displayAction(const player *p, card *c, int32_t type)
{
    char printmessage[100] = {0};
    for (int32_t i = 0; i < 200; i++)
    {
        strmessage[i] = 0;
    }
    if (type == 1)
    {
        strcat(strmessage, "SUCCESS: ");
    }
    else if (type == 2)
    {
        strcat(strmessage, "FAILED: ");
    }
    else if (type == 3 || type == 5)
    {
        strcat(strmessage, "Action: ");
    }
    else if (type == 4 || type == 6)
    {
        strcat(strmessage, "Warning: ");
    }

    strcat(strmessage, "Player ");
    strcat(printmessage, "Player ");
    strcat(strmessage, p->_name);
    strcat(printmessage, p->_name);
    if (type != 5 && type != 6)
    {
        strcat(strmessage, " used");
        strcat(printmessage, " used");
        strcat(strmessage, c->_name);
        strcat(printmessage, c->_name);
        if (strncmp("BANG", c->_name, 4) == 0)
        {
            strcat(printmessage, "( ☉_☉)≡☞o────。。。"); // bang
        }
        if (strncmp("MANCATO", c->_name, 4) == 0)
        {
            strcat(printmessage, "🛡️"); // missed
        }
        if (strncmp("BIRRA", c->_name, 4) == 0)
        {
            strcat(printmessage, "🍻💉"); // beer
        }
        if (strncmp("SALOON", c->_name, 4) == 0)
        {
            strcat(printmessage, "🍷🍸🍹🥂"); // saloon
        }
        if (strncmp("WELLSFARGO", c->_name, 4) == 0)
        {
            strcat(printmessage, "🃏🃏🃏"); // wellsfargo
        }
        if (strncmp("DILIGENZA", c->_name, 4) == 0)
        {
            strcat(printmessage, "🃏🃏"); // DILIGENZA
        }
        if (strncmp("EMPORIO", c->_name, 4) == 0)
        {
            strcat(printmessage, "🏪"); // generalstore
        }
        if (strncmp("PANICOI", c->_name, 4) == 0)
        {
            strcat(printmessage, "Σ┗(＠ロ＠;)┛"); // panic
        }
        if (strncmp("CATBALOU", c->_name, 4) == 0)
        {
            strcat(printmessage, "❌🚮"); // catbalou
        }
        if (strncmp("GATLING", c->_name, 4) == 0)
        {
            strcat(printmessage, "🔫"); // gatling
        }
        if (strncmp("INDIANI", c->_name, 4) == 0)
        {
            strcat(printmessage, "(╯>д<)╯"); // INDIANI
        }
        if (strncmp("DUELLO", c->_name, 4) == 0)
        {
            strcat(printmessage, "🤼"); // duel
        }

        if (strncmp("MUSTANG", c->_name, 4) == 0 || strncmp("APPALOOSA", c->_name, 4) == 0)
        {
            strcat(printmessage, "🐎"); // stagecoach
        }
        if (strncmp("BARREL", c->_name, 4) == 0)
        {
            strcat(printmessage, "🗯🍺"); // BARREL
        }
        if (strncmp("PRIGIONE", c->_name, 4) == 0)
        {
            strcat(printmessage, "🚔"); // jail
        }
        if (strncmp("DINAMITE", c->_name, 4) == 0)
        {
            strcat(printmessage, "💣"); // dinamite
        }
    }
    if (type == 1 || type == 3)
    {
        strcat(strmessage, " successed");
    }
    else if (type == 2 || type == 4)
    {
        strcat(strmessage, " failed");
    }
    else if (type == 5)
    {
        strcat(printmessage, " draw a card 🃏 ξ( ✿＞◡❛)!");
        strcat(strmessage, " draw a card ξ( ✿＞◡❛)!");
    }
    else if (type == 6)
    {
        strcat(printmessage, " can't draw a card 🃏 (｡•́︿•̀｡)");
        strcat(strmessage, " can't draw a card (｡•́︿•̀｡)");
    }
    printf("%s\n", printmessage);
    return strmessage;
}
char *judge(player *p, card *c, game *game) //判定
{
    if (strncmp("BARREL", c->_name, 6) == 0)
    {
        draw(p, game);
        if (p->_hand[p->_hand_cnt - 1]->_suit == 2)
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 1); // "SUCCESS: " [0] = 'S'
        }
        else
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 2); // "FAILED: " [0] = 'F'
        }
    }
    else if (strncmp("PRIGIONE", c->_name, 8) == 0)
    {
        draw(p, game);
        if (p->_hand[p->_hand_cnt - 1]->_suit == 2)
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 1);
        }
        else
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 2);
        }
    }
    else if (strncmp("DINAMITE", c->_name, 8) == 0)
    {
        draw(p, game);
        if (p->_hand[p->_hand_cnt - 1]->_suit == 1 && (p->_hand[p->_hand_cnt - 1]->_number >= 2 && p->_hand[p->_hand_cnt - 1]->_number <= 9))
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 1);
        }
        else
        {
            if (p->_position + 1 > game->_total_player_cnt)
            {
                game->_player[0]->_dinamite = c;
                p->_dinamite = NULL;
            }
            else
            {
                (p + 1)->_dinamite = c;
                p->_dinamite = NULL;
            }
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 2);
        }
    }
    else
    {
        return displayAction(p, c, 0);
    }
    return displayAction(p, c, 0);
}