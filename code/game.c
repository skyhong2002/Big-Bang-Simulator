#include "game.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char LOGFILE_NAME[FILENAME_MAX] = "log.txt";

void saveLogInit(game *bang){
    strcpy(LOGFILE_NAME, bang->_logfile_name);
    char *fname = LOGFILE_NAME;
    FILE *f;
    if ((f = fopen(fname, "w")) == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    fprintf(f, "Game Player: %d\n", bang->_total_player_cnt);
    for(int i = 0; i < bang->_total_player_cnt; ++i){
        player *p = bang->_player[i];
        fprintf(f, "\n%s (ID: %d, MAXHP: %d)\n", p->_name, p->_id, p->_max_hp);
        fprintf(f, "identity: %s\n", p->_identity);
        fprintf(f, "role:     %s\nHandcard:\n", p->_role->_name);
        for(int j = 0; j < p->_hand_cnt; ++j)
            fprintf(f, "\t%d: %s\n", j, p->_hand[j]->_name);
    }
    fprintf(f, "\nBANG! Game start\n");
    
    fclose(f);
}

void saveLog(char *message)
{
    char *fname = LOGFILE_NAME;
    FILE *f;
    if ((f = fopen(fname, "a")) == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    fprintf(f, "%s\n", message);
    fclose(f);
}

char *isGameEnd(game *bang)
{   
    // 確認死亡人數有沒有減少
    uint8_t alivecnt = 0;
    for(int i = 0; i < bang->_total_player_cnt; ++i)
        if(bang->_player[i]->_hp > 0) ++alivecnt;
    // 更新 pos, _alive_cnt
    if(alivecnt < bang->_alive_player_cnt){
        printf("New player died. Change position.\n");
        bang->_alive_player_cnt = alivecnt;
        alivecnt = 0;
        for(int i = 0; i < bang->_total_player_cnt; ++i){
            if(bang->_player[i]->_hp > 0){
                ++alivecnt;
                bang->_player[i]->_position = alivecnt;
            }
        }
    }
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
    else if (!Sceriffo && Fuorilecce)
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
    strcpy(LOGFILE_NAME, bang->_logfile_name);
    saveLogInit(bang);
    int32_t total_turn = 0;
    char *winner = "Nobody";
    while (total_turn <= 20 && total_turn >= 0)
    {
        ++total_turn;
        player *cplayer = bang->_player[bang->_turn]; // current player

        printf("\nTurn " YEL "%d" RESET ":", total_turn);
        saveLog("---------------------");
        // Judge Dynamite
        if (cplayer->_dinamite != NULL)
        {
            printf("You have a Dynamite, judging...\n");
            char *m = {0};
            m = judge(cplayer, cplayer->_dinamite, bang);
            if(strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && m[0] == 'F'){
                // hp +3
                changeHP(cplayer, 3, bang);
                m = judge(cplayer, cplayer->_dinamite, bang);
            }

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
                    saveLog(beer(cplayer, cplayer->_hand[i], bang));
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
            char *m = {0};
            m = judge(cplayer, cplayer->_jail, bang);
            if(strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && m[0] == 'F'){
                m = judge(cplayer, cplayer->_jail, bang);
            }
            if (m[0] == 'F')
            {
                printf("Stay in jail for one turn.\n");
                continue;
            }
        }
        if (strncmp(cplayer->_role->_name, "JesseJones", 10) == 0)
        {
            printf("JesseJones can draw a card from others!\n");
            if(cplayer->_id == 0)
            {
                int32_t Jessechoice = 0;
                printf("Which player do you want to draw?\n");
                for(int32_t i = 1; i<bang->_total_player_cnt; i++)
                {
                    if(!isDead(bang->_player[i]))
                    {
                        printf("%d: draw a card from %s\n", i, bang->_player[i]->_name);
                    }
                }
                printf("---------------------\n");
                printf("Choice: ");
                scanf("%d", &Jessechoice);
                drawplayer(cplayer, bang->_player[Jessechoice], 2);
            }
            else // computer
            {
                for(int32_t i = 1; i<bang->_total_player_cnt; i++)
                {
                    if(!isDead(bang->_player[i]))
                    {
                        drawplayer(cplayer, bang->_player[i], 2);
                        break;
                    }
                }                
            }
            draw(cplayer, bang);
        }
        else
        {
            // get 2 card;
            draw(cplayer, bang);
            draw(cplayer, bang);            
        }

        if (strncmp(cplayer->_role->_name, "BlackJack", 9) == 0 && cplayer->_id == 0)
        {
            while(1)
            {
                int32_t choiceblack = 0;
                printf("Do you want to display your second card?\n");
                printf("1: Yes\n2: No\nYour choice: ");
                scanf("%d", &choiceblack);
                if(choiceblack == 1)
                {
                    if(cplayer->_hand[cplayer->_hand_cnt-1]->_suit == 2 || cplayer->_hand[cplayer->_hand_cnt-1]->_suit == 3)
                    {
                        draw(cplayer, bang);
                    }
                    break;
                }
                else if(choiceblack==2)
                {
                    printf("Ok\n");
                    break;
                }
                else
                {
                    printf("Your input is wrong.\n");
                    continue;
                }               
            }

        }

        displayPlayer(cplayer);

        while (!isDead(cplayer) && !isGameEnd(bang))
        {
            int32_t opt = -1;
            int32_t action = -2;
            while (opt == -1 || action == -2)
            {
                opt = getOption(bang, cplayer);
                if (opt > cplayer->_hand_cnt){
                    printf("No card selected. Try again.\n");
                    continue;
                }
                if (opt == 0) break;
                action = getAction(bang, cplayer->_hand[opt-1]);
            }
            if (opt == 0)
            {
                if(cplayer->_hand_cnt > cplayer->_hp)
                {
                    printf("Your cards are more than your hp. Please keep used your cards.\n");
                    continue;
                }
                else
                {
                    break;
                } 
            }
            card *targetcard = cplayer->_hand[opt-1];
            player *target = bang->_player[action];
            if(action == -1){ // throwcard
                discard(cplayer, targetcard, 2, bang);
            }
            else{
                char *msg = "Warning: No valid action.";
                // Action
                if (strncmp(targetcard->_name, "BANG", 4) == 0 ||
                    strncmp(targetcard->_name, "MANCATO", 4) == 0){
                    msg = bangAction(cplayer, targetcard, target, bang);

                    
                    bool is_sucess = false;
                    if(target->_barrel) {
                        char *mes = {0};
                        mes = judge(target, target->_barrel, bang);
                        if(strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && mes[0] == 'F'){
                            mes = judge(target, target->_barrel, bang);
                        }
                        is_sucess = (mes[0] == 'F'?false:true);
                    }
                    if(!is_sucess){
                        for(int i = 0; i < target->_hand_cnt; ++i){
                            if(strncmp(target->_hand[i]->_name, "MANCATO", 4) == 0 ||
                            (strncmp(target->_hand[i]->_name, "BANG", 4) == 0 &&
                            strncmp(target->_role->_name, "CalamityJanet", 4) == 0))
                                missed(target, target->_hand[i], bang);
                        }
                    }
                    if (strncmp(cplayer->_role->_name, "SlabTheKiller", 13) == 0 && is_sucess){
                        printf("ROLE Effect: SlabTheKiller (double miss)\n");
                        changeHP(target, -1, bang);
                        is_sucess = false;
                        if(target->_barrel) {
                            char *mes = {0};
                            mes = judge(target, target->_barrel, bang);
                            if(strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && mes[0] == 'F'){
                                mes = judge(target, target->_barrel, bang);
                            }
                            is_sucess = (mes[0] == 'F'?false:true);
                        }
                        if(!is_sucess){
                            for(int i = 0; i < target->_hand_cnt; ++i){
                                if(strncmp(target->_hand[i]->_name, "MANCATO", 4) == 0 ||
                                (strncmp(target->_hand[i]->_name, "BANG", 4) == 0 &&
                                strncmp(target->_role->_name, "CalamityJanet", 4) == 0))
                                    missed(target, target->_hand[i], bang);
                            }
                        }
                    }
                } else if (strncmp(targetcard->_name, "DUELLO", 4) == 0){
                    msg = duel(cplayer, targetcard, target, bang);
                } else if (strncmp(targetcard->_name, "PANICOI", 4) == 0){
                    msg = panic(cplayer, targetcard, target, bang);
                } else if (strncmp(targetcard->_name, "CATBALOU", 4) == 0){
                    msg = catBalou(cplayer, targetcard, target, bang);
                }
                // Action self
                  else if (strncmp(targetcard->_name, "DILIGENZA", 4) == 0){
                    msg = stageCoach(cplayer, targetcard, bang);
                } else if (strncmp(targetcard->_name, "WELLSFARGO", 4) == 0){
                    msg = wellsFargo(cplayer, targetcard, bang);
                } else if (strncmp(targetcard->_name, "BIRRA", 4) == 0){
                    if(cplayer->_hp == cplayer->_max_hp){
                        printf("Your HP is full.\n");
                        continue;
                    }
                    msg = beer(cplayer, targetcard, bang);
                }
                // Action All
                  else if (strncmp(targetcard->_name, "EMPORIO", 4) == 0){
                    msg = generalStore(cplayer, targetcard, bang);
                } else if (strncmp(targetcard->_name, "INDIANI", 4) == 0){
                    msg = indians(cplayer, targetcard, bang);
                } else if (strncmp(targetcard->_name, "GATLING", 4) == 0){
                    msg = gatling(cplayer, targetcard, bang);
                } else if (strncmp(targetcard->_name, "SALOON", 4) == 0){
                    msg = saloon(cplayer, targetcard, bang);
                }
                // Equip
                  else if (strncmp(targetcard->_skill, "Equipment", 4) == 0){
                    equip(cplayer, targetcard, target, bang);
                     // todo: bool -> char*
                } else {
                    // printf("Warning: No valid action.");
                }
                // saveLog(msg);
            }
        }

        printf("Turn %d end.\n", total_turn);
        winner = isGameEnd(bang);
        if (winner){
            printf("GAME end. (total turn: %d)\n", total_turn);
            break;
        }
        do
        {
            bang->_turn = (bang->_turn + 1) % bang->_total_player_cnt;
        } while (isDead(bang->_player[bang->_turn]));
    }
    return winner;
}
/*
need to check
    棄牌堆 to 牌堆
    某個陣營贏
    bang 的次數（無限）
    確認每張牌
    choice buffer 更改
    if (strncmp(cplayer->_role->_name, "KitCarlson", 10) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "PedroRamirez", 12) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "SidKetchum", 12) == 0)
    {
    }
    if (strncmp(cplayer->_role->_name, "SuzyLafayette", 13) == 0)
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
    int32_t want = -1;
    while(want < 0 || want > p->_hand_cnt){
        printf("---------------------\n");
        for (int i = 0; i < bang->_total_player_cnt; ++i)
        {
            printf("%s", bang->_player[i]->_name);
            if (strncmp(bang->_player[i]->_identity, "Sceriffo", 4) == 0)
                printf("🚔");
            if (bang->_player[i]->_position == p->_position)
                printf(BLU"(YOU)" RESET);
            printf("(%d) ", bang->_player[i]->_hp);
        }
        printf("\n");
        if(p->_id == 0){
            printf("What do you want to do?\n");
            printf("0: End turn.\n");
            displayHandCard(p);
            printf("---------------------\nYour Choice " YEL "> " RESET);
            char order[256] = {0};
            char *tmp;
            tmp = calloc(4100, sizeof(char));
            fflush(stdin);
            fgets( order, sizeof( order ), stdin );
            want = strtol(order, &tmp, 10);
            // scanf("%d", &want);
        }
        else{
            printf("%s's Choice " BLU "> " RESET, p->_name);
            time_t t;
            srand((unsigned) time(&t));
            want = rand() % (p->_hand_cnt + 1);
            if(rand()%3 < 1) want = 0; //hard mode
            // sleep((1+(rand() % 3))/3);
            printf("%d\n", want);
            // sleep(1);
        }
    }
    return want;
}

int32_t getAction(game *bang, card *c)
{
    int32_t want = -2;

    if(bang->_player[bang->_turn]->_id == 0){
        // -2 返回, -1 丟掉, 自己用/對所有人用, 對特定人用
        printf("---------------------\n");
        printf("Card "YEL"%s"RESET" info:\n%s\n", c->_name, c->_skill);
        printf("---------------------\n");
        printf("-2: Return to your handcard.\n");
        printf("-1: Move to trash.\n");
        if(strncmp("Action:", c->_skill, 7) == 0 ||
        strncmp("DINAMITE", c->_name, 8) == 0 ||
        strncmp("PRIGIONE", c->_name, 8) == 0){
            for(int i = 0; i < bang->_total_player_cnt; ++i){
                if(isDead(bang->_player[i])) continue;
                if(i == bang->_turn) continue; // printf(BLU"(YOU)"RESET)
                printf("%d: Use the card to %s", i, bang->_player[i]->_name);
                printf("\n");
            }
        }
        else{
            printf("0: Use/Equip the card to yourself.\n");
        }
        printf("---------------------\nYour Action " YEL "> " RESET);
        char order[256] = {0};
        char *tmp;
        tmp = calloc(4100, sizeof(char));
        fflush(stdin);
        fgets( order, sizeof( order ), stdin );
        want = strtol(order, &tmp, 10);
        //scanf("%d", &want);
    }
    else{
        printf("---------------------\n%s's Action " BLU "> " RESET, bang->_player[bang->_turn]->_name);
        time_t t;
        srand((unsigned) time(&t));
        want = (rand() % (bang->_player[bang->_turn]->_hand_cnt + 3))-2;
        if(rand()%3 < 1) want = 0;
        // sleep((1+(rand() % 3))/3);
        printf("%d\n", want);
        // sleep(1);
    }
    if((strncmp("Action:", c->_skill, 7) == 0 ||
        strncmp("DINAMITE", c->_name, 8) == 0 ||
        strncmp("PRIGIONE", c->_name, 8) == 0)){
        if(want < -2 || want >= bang->_total_player_cnt){
            printf("Your action is illegal. Try again.\n");
            return -2;
        }
        if(want >= 0){
            if(isDead(bang->_player[want])){
                printf("This player is dead. Try again.\n");
                return -2;
            }
        }
        return want;
    }
    else {
        if(want < -2 || want > 0){
            printf("Your action is illegal. Try again.\n");
            return -2;
        }
        if(want == 0) want = bang->_turn;
        return want; 
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
    printf("identity  : %s\n", (p->_id == 0 || strncmp(p->_identity, "Sceriffo", 4) == 0? p->_identity : "TOP SECRET"));
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
char* displayAction(const player *p, card *c, int32_t type)
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
    else if (type == 3 || type == 5 || type == 7)
    {
        strcat(strmessage, "Action: ");
    }
    else if (type == 4 || type == 6 || type == 8)
    {
        strcat(strmessage, "Warning: ");
    }
    if(type != 9)
    {
        //strcat(strmessage, "Player ");
        //strcat(printmessage, "Player ");
        strcat(strmessage, p->_name);
        strcat(printmessage, p->_name);
    }
    if (type != 5 && type != 6 && type != 7 && type != 8 && type != 9)
    {
        if(type == 3 || type == 4)
        {
            strcat(strmessage, " used ");
            strcat(printmessage, " used ");
        }
        else if(type == 1 || type == 2)
        {
            strcat(strmessage, " equiped ");
            strcat(printmessage, " equiped ");            
        }
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
        strcat(printmessage, " successed");
    }
    else if (type == 2 || type == 4)
    {
        strcat(strmessage, " failed");
        strcat(printmessage, " failed");
    }
    else if (type == 5 || type == 9)
    {
        strcat(printmessage, " draw a card 🃏 ξ( ✿＞◡❛)!");
        strcat(strmessage, " draw a card ξ( ✿＞◡❛)!");
    }
    else if (type == 6)
    {
        strcat(printmessage, " can't draw a card 🃏 (｡•́︿•̀｡)");
        strcat(strmessage, " can't draw a card (｡•́︿•̀｡)");
    }
    else if (type == 7)
    {
        strcat(printmessage, " discard ");
        strcat(printmessage, c->_name);
        strcat(printmessage, " 🃏 ξ( ✿＞◡❛)!");
        strcat(strmessage, " discard ");
        strcat(strmessage, c->_name);
        strcat(strmessage, " 🃏 ξ( ✿＞◡❛)!");
    }
    else if (type == 8)
    {
        strcat(printmessage, " can't discard ");
        strcat(printmessage, c->_name);
        strcat(printmessage, " 🃏 (｡•́︿•̀｡)");
        strcat(strmessage, " can't discard ");
        strcat(strmessage, c->_name);
        strcat(strmessage, " 🃏 (｡•́︿•̀｡)");
    }
    printf("%s\n", printmessage);
    saveLog(strmessage);
    return strmessage;
}
char *judge(player *p, card *c, game *game) //判定
{
    draw(p, game);
    char *msg = {0};
    strcat(msg, p->_hand[p->_hand_cnt - 1]->_name);
    strcat(msg, ": ");
    switch(p->_hand[p->_hand_cnt - 1]->_suit){
    case 1:
        strcat(msg, "♠");
        break;
    case 2:
        strcat(msg, "♥");
        break;
    case 3:
        strcat(msg, "♦");
        break;
    case 4:
        strcat(msg, "♣");
        break;
    }
    char tempt[2] = {0};
    tempt[0] = p->_hand[p->_hand_cnt - 1]->_number/10 + '0';
    strcat(msg, tempt);
    tempt[0] = p->_hand[p->_hand_cnt - 1]->_number%10 + '0';
    strcat(msg, tempt);
    printf("%s\n", msg);
    saveLog(msg);
    // ♠♥♦♣
    // printf p->_hand[p->_hand_cnt - 1]
    if (strncmp("BARREL", c->_name, 6) == 0)
    {
        if (p->_hand[p->_hand_cnt - 1]->_suit == 2)
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            changeHP(p, 1, game);
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
        if (p->_hand[p->_hand_cnt - 1]->_suit == 1 && (p->_hand[p->_hand_cnt - 1]->_number >= 2 && p->_hand[p->_hand_cnt - 1]->_number <= 9))
        {
            discard(p, c, 1, game);
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            changeHP(p, -3, game);
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