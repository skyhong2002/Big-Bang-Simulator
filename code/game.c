#include "game.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>  

char LOGFILE_NAME[FILENAME_MAX] = "log.txt";
int32_t Sidchoice = 0;

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void saveLogInit(game *bang)
{
    strcpy(LOGFILE_NAME, bang->_logfile_name);
    char *fname = LOGFILE_NAME;
    FILE *f;
    if ((f = fopen(fname, "w")) == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }
    fprintf(f, "Game Player: %d\n", bang->_total_player_cnt);
    for (int i = 0; i < bang->_total_player_cnt; ++i)
    {
        player *p = bang->_player[i];
        fprintf(f, "\n%s (ID: %d, MAXHP: %d)\n", p->_name, p->_id, p->_max_hp);
        fprintf(f, "identity: %s\n", p->_identity);
        fprintf(f, "role:     %s\nHandcard:\n", p->_role->_name);
        for (int j = 0; j < p->_hand_cnt; ++j)
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
    if(message[0] != 'W' || strncmp(message, "FAILED:", 7) != 0)
        fprintf(f, "%s\n", message);
    fclose(f);
}

char *isGameEnd(game *bang)
{
    time_t t;
    srand((unsigned)time(&t));
    // 確認死亡人數有沒有減少
    uint8_t alivecnt = 0;
    for (int i = 0; i < bang->_total_player_cnt; ++i)
        if (bang->_player[i]->_hp > 0)
            ++alivecnt;
    // 更新 pos, _alive_cnt
    if (alivecnt < bang->_alive_player_cnt)
    {
        // printf("New player died. Changing position.\n");
        bang->_alive_player_cnt = alivecnt;
        alivecnt = 0;
        int8_t VultureSamID = -1;
        for (int i = 0; i < bang->_total_player_cnt; ++i){
            if (bang->_player[i]->_hp > 0){
                if(strncmp(bang->_player[i]->_role->_name, "VultureSam", 10) == 0){
                    VultureSamID = bang->_player[i]->_id;
                }
                ++alivecnt;
                bang->_player[i]->_position = alivecnt;
            }
        }
        // 搜刮 have dead player cards
        // me->VultureSam dead->dead
        for (int i = 0; i < bang->_total_player_cnt; ++i){
            if(bang->_player[i]->_hp > 0) continue;
            if(bang->_player[i]->_hand_cnt > 0 ||
               bang->_player[i]->_dinamite != NULL ||
               bang->_player[i]->_barrel != NULL ||
               bang->_player[i]->_gun != NULL ||
               bang->_player[i]->_horse != NULL ||
               bang->_player[i]->_jail  != NULL ){
                player *dead = bang->_player[i];
                printf("Plunder %s!\n", dead->_name);
                printf("Player identity is %s\n", dead->_identity);
                if(VultureSamID == -1){ // No VultureSam
                    for(int32_t i = 0; i < dead->_hand_cnt; i++){
                        discard(dead, dead->_hand[0], 2, bang);
                    }
                    if(dead->_dinamite != NULL) discard(dead, dead->_dinamite, 1, bang);
                    if(dead->_barrel != NULL) discard(dead, dead->_barrel, 1, bang);
                    if(dead->_gun != NULL) discard(dead, dead->_gun, 1, bang);
                    if(dead->_horse != NULL) discard(dead, dead->_horse, 1, bang);
                    if(dead->_jail != NULL) discard(dead, dead->_jail, 1, bang);
                    dead->_dinamite == NULL;
                    dead->_barrel == NULL;
                    dead->_gun == NULL;
                    dead->_horse == NULL;
                    dead->_jail == NULL;
                }
                else{
                    printf("ROLE effect: VultureSam (plunder dead man's body)\n");
                    player *sam = bang->_player[VultureSamID];
                    for(int32_t i = 0; i < dead->_hand_cnt; i++)
                    {
                        drawplayer(sam, dead, 2);
                        i = 0;
                    }
                    for(int32_t i = 0; i < 5; i++)
                    {
                        drawplayer(sam, dead, 1);
                    }
                }
            }
        }

    }
    bool Sceriffo = false;
    bool Fuorilecce = false;
    bool Rinnecato = false;
    for (int i = 0; i < bang->_total_player_cnt; ++i)
    {
        if (bang->_player[i]->_hp <= 0)
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
    while (total_turn >= 0) // && total_turn <= 20
    {
        ++total_turn;
        player *cplayer = bang->_player[bang->_turn]; // current player

        printf("\nTurn " YEL "%d" RESET ":\n", total_turn);
        saveLog("---------------------");
        // Judge Dynamite
        if (cplayer->_dinamite != NULL)
        {
            printf("Dynamite on %s, judging...\n", cplayer->_name);
            char *m = {0};
            m = judge(cplayer, cplayer->_dinamite, bang);
            cplayer->_dinamite = NULL;
            if(bang->_discard[bang->_discard_cnt-1] == NULL)
                printf("Warning: dinamite card disappear.\n");
            if (strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && m[0] == 'F')
            {
                // hp +3
                changeHP(cplayer, 3, bang);
                m = judge(cplayer, cplayer->_dinamite, bang);
            }
        }
        // use beer to recover
        while (cplayer->_hp <= 0)
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
        // Judge Jail
        if (cplayer->_jail != NULL)
        {
            printf("Jail on %s, judging...\n", cplayer->_name);
            char *m = {0};
            m = judge(cplayer, cplayer->_jail, bang);
            if(strncmp(bang->_discard[bang->_discard_cnt-1]->_name, "PRIGIONE", 5) != 0)
                printf("Warning: jail card disappear.\n");
            if (strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && m[0] == 'F')
            {
                m = judge(cplayer, cplayer->_jail, bang);
            }
            cplayer->_jail = NULL;
            if (m[0] == 'F')
            {
                printf("Stay in jail for one turn.\n");
                do {
                    bang->_turn = (bang->_turn + 1) % bang->_total_player_cnt;
                } while (bang->_player[bang->_turn]->_hp <= 0);
                continue;
            }
        }
        // draw 2 card
        if (strncmp(cplayer->_role->_name, "JesseJones", 10) == 0)
        {
            printf("JesseJones can draw a card from others!\n");
            if (cplayer->_id == 0)
            {
                int32_t Jessechoice = 0;
                printf("Which player do you want to draw?\n");
                for (int32_t i = 1; i < bang->_total_player_cnt; i++)
                {
                    if (!isDead(bang->_player[i]))
                    {
                        printf("%d: draw a card from %s\n", i, bang->_player[i]->_name);
                    }
                }
                printf("---------------------\n");
                printf("Choice: ");
                scanf("%d", &Jessechoice);
                fflush(stdin);
                drawplayer(cplayer, bang->_player[Jessechoice], 2);
            }
            else // computer
            {
                for (int32_t i = 1; i < bang->_total_player_cnt; i++)
                {
                    if (!isDead(bang->_player[i]))
                    {
                        drawplayer(cplayer, bang->_player[i], 2);
                        break;
                    }
                }
            }
            draw(cplayer, bang);
        }
        else if (strncmp(cplayer->_role->_name, "KitCarlson", 10) == 0 && cplayer->_id == 0)
        {
            int32_t Kitchoice1 = 0, Kitchoice2 = 0;
            if (bang->_deck_cnt <= 3)
            {
                for (int32_t i = 0; bang->_deck_cnt < 3; i++)
                {
                    bang->_deck[bang->_deck_cnt - 1] = bang->_discard[bang->_discard_cnt - 1];
                    bang->_deck_cnt += 1;
                    bang->_discard_cnt -= 1;
                }
            }
            printf("KitCarlson can choose two cards between three cards!\n");
            printf("1: %s\n", bang->_deck[bang->_deck_cnt - 1]->_name);
            printf("2: %s\n", bang->_deck[bang->_deck_cnt - 2]->_name);
            printf("3: %s\n", bang->_deck[bang->_deck_cnt - 3]->_name);
            printf("---------------------\n");
            printf("Choice(input 2 numbers, ex. 1 2): ");
            scanf("%d %d", &Kitchoice1, &Kitchoice2);
            fflush(stdin);
            if (Kitchoice1 == 1 && Kitchoice2 == 2)
            {
                draw(cplayer, bang);
                draw(cplayer, bang);
            }
            else if (Kitchoice1 == 1 && Kitchoice2 == 3)
            {
                draw(cplayer, bang);
                cplayer->_hand_cnt += 1;
                cplayer->_hand[cplayer->_hand_cnt - 1] = bang->_deck[bang->_deck_cnt - 3];
                bang->_deck[bang->_deck_cnt - 3] = bang->_deck[bang->_deck_cnt - 2];
                bang->_deck_cnt -= 1;
                displayAction(cplayer, NULL, 5);
            }
            else if (Kitchoice1 == 2 && Kitchoice2 == 3)
            {
                cplayer->_hand_cnt += 1;
                cplayer->_hand[cplayer->_hand_cnt - 1] = bang->_deck[bang->_deck_cnt - 2];
                cplayer->_hand_cnt += 1;
                cplayer->_hand[cplayer->_hand_cnt - 1] = bang->_deck[bang->_deck_cnt - 3];
                bang->_deck[bang->_deck_cnt - 3] = bang->_deck[bang->_deck_cnt - 1];
                bang->_deck_cnt -= 2;
                displayAction(cplayer, NULL, 5);
                displayAction(cplayer, NULL, 5);
            }
        }
        else if (strncmp(cplayer->_role->_name, "PedroRamirez", 12) == 0)
        {
            printf("PedroRamirez first card from discard cards!\n");
            if(bang->_discard_cnt == 0)
            {
                printf("But there is no cards in discard area.\nJust draw card from desk.\n");
                draw(cplayer, bang);
                draw(cplayer, bang);
            }
            else
            {
                cplayer->_hand_cnt += 1;
                cplayer->_hand[cplayer->_hand_cnt - 1] = bang->_discard[bang->_discard_cnt - 1];
                bang->_discard_cnt -= 1;
                displayAction(cplayer, NULL, 5);
                draw(cplayer, bang);
            }  
        }
        else
        {
            // get 2 card;
            draw(cplayer, bang);
            draw(cplayer, bang);
        }
        if (strncmp(cplayer->_role->_name, "BlackJack", 9) == 0 && cplayer->_id == 0)
        {
            while (1)
            {
                int32_t choiceblack = 0;
                printf("You are BlackJack. Do you want to display your second card?\n");
                printf("1: Yes\n2: No\nYour choice: ");
                scanf("%d", &choiceblack);
                fflush(stdin);
                if (choiceblack == 1)
                {
                    printf("Card %s suit is %d.\n", cplayer->_hand[cplayer->_hand_cnt - 1]->_name, cplayer->_hand[cplayer->_hand_cnt - 1]->_suit);
                    if (cplayer->_hand[cplayer->_hand_cnt - 1]->_suit == 2 || cplayer->_hand[cplayer->_hand_cnt - 1]->_suit == 3)
                    {
                        printf("You can draw one card more.\n");
                        draw(cplayer, bang);
                    }
                    else
                    {
                        printf("Judge failed.\n");
                    }
                    break;
                }
                else if (choiceblack == 2)
                {
                    printf("Ok. Nothing happened.\n");
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

        int32_t bang_cnt = 0;
        Sidchoice = 0;
        while (!isDead(cplayer) && !isGameEnd(bang)) // realgameloop
        {
            int32_t opt = 0;
            int32_t action = -2;
            while (opt == 0 || action == -2)
            {
                opt = getOption(bang, cplayer);
                if (opt == -1){
                    break;
                }
                if (opt > cplayer->_hand_cnt || opt == 0)
                {
                    printf("Invalid option. Try again.\n");
                    continue;
                }
                action = getAction(bang, cplayer->_hand[opt - 1]);
            }
            if (opt == -1)
            {
                if (cplayer->_hand_cnt > cplayer->_hp)
                {
                    printf("Warning: Your cards are more than your hp. Please keep used your cards.\n");
                    continue;
                }
                else
                {
                    printf("END TURN\n");
                    break;
                }
            }
            card *targetcard = cplayer->_hand[opt - 1];
            player *target = bang->_player[action];
            if (action == -1)
            { // throwcard
                discard(cplayer, targetcard, 2, bang);
                if (strncmp(cplayer->_role->_name, "SidKetchum", 12) == 0)
                {
                    printf("When SidKetchum discard two cards, he can gain one hp.\n");
                    Sidchoice += 1;
                    if (Sidchoice % 2 == 0)
                    {
                        changeHP(cplayer, 1, bang);
                    }
                }
            }
            else
            {
                char *msg = "Warning: No valid action.";
                // Action
                if (strncmp(targetcard->_name, "BANG", 4) == 0 ||
                    (strncmp(targetcard->_name, "MANCATO", 4) == 0 &&
                    strncmp(cplayer->_role->_name, "CalamityJanet", 11) == 0))
                {
                    // unlimit bang 
                    if(cplayer->_gun != NULL)
                        if(strncmp(cplayer->_gun->_name, "VOLCANIC", 7) == 0)
                            bang_cnt = 0;
                    if(strncmp(cplayer->_role->_name, "WillyTheKid", 11) == 0)
                        bang_cnt = 0;
                    if(bang_cnt == 0){
                        msg = bangAction(cplayer, targetcard, target, bang);
                        if(msg[0] == 'W') continue;
                        ++bang_cnt;
                        bool is_sucess = false;
                        if (target->_barrel)
                        {
                            char *mes = {0};
                            mes = judge(target, target->_barrel, bang);
                            if (strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && mes[0] == 'F')
                            {
                                printf("ROLE Effect: LuckyDuke (double judge)\n");
                                mes = judge(target, target->_barrel, bang);
                            }
                            is_sucess = (mes[0] == 'F' ? false : true);
                        }
                        if (!is_sucess)
                        {
                            for (int i = 0; i < target->_hand_cnt; ++i)
                            {
                                if (strncmp(target->_hand[i]->_name, "MANCATO", 4) == 0 ||
                                    (strncmp(target->_hand[i]->_name, "BANG", 4) == 0 &&
                                    strncmp(target->_role->_name, "CalamityJanet", 4) == 0)){
                                    missed(target, target->_hand[i], bang);
                                    break;
                                }
                            }
                        }
                        if (strncmp(cplayer->_role->_name, "SlabTheKiller", 13) == 0 && is_sucess)
                        {
                            printf("ROLE Effect: SlabTheKiller (double miss)\n");
                            changeHP(target, -1, bang);
                            is_sucess = false;
                            if (target->_barrel)
                            {
                                char *mes = {0};
                                mes = judge(target, target->_barrel, bang);
                                if (strncmp(cplayer->_role->_name, "LuckyDuke", 9) == 0 && mes[0] == 'F')
                                {
                                    printf("ROLE Effect: LuckyDuke (double judge)\n");
                                    mes = judge(target, target->_barrel, bang);
                                }
                                is_sucess = (mes[0] == 'F' ? false : true);
                            }
                            if (!is_sucess)
                            {
                                for (int i = 0; i < target->_hand_cnt; ++i)
                                {
                                    if (strncmp(target->_hand[i]->_name, "MANCATO", 4) == 0 ||
                                        (strncmp(target->_hand[i]->_name, "BANG", 4) == 0 &&
                                        strncmp(target->_role->_name, "CalamityJanet", 4) == 0))
                                        missed(target, target->_hand[i], bang);
                                }
                            }
                        }
                    }
                    else{
                        printf("Warning: You can use BANG only once.\n");
                    }
                }
                else if (strncmp(targetcard->_name, "DUELLO", 4) == 0)
                {
                    msg = duel(cplayer, targetcard, target, bang);
                }
                else if (strncmp(targetcard->_name, "PANICOI", 4) == 0)
                {
                    msg = panic(cplayer, targetcard, target, bang);
                }
                else if (strncmp(targetcard->_name, "CATBALOU", 4) == 0)
                {
                    msg = catBalou(cplayer, targetcard, target, bang);
                }
                // Action self
                else if (strncmp(targetcard->_name, "DILIGENZA", 4) == 0)
                {
                    msg = stageCoach(cplayer, targetcard, bang);
                }
                else if (strncmp(targetcard->_name, "WELLSFARGO", 4) == 0)
                {
                    msg = wellsFargo(cplayer, targetcard, bang);
                }
                else if (strncmp(targetcard->_name, "BIRRA", 4) == 0)
                {
                    if (cplayer->_hp == cplayer->_max_hp)
                    {
                        printf("Your HP is full.\n");
                        continue;
                    }
                    msg = beer(cplayer, targetcard, bang);
                }
                // Action All
                else if (strncmp(targetcard->_name, "EMPORIO", 4) == 0)
                {
                    msg = generalStore(cplayer, targetcard, bang);
                }
                else if (strncmp(targetcard->_name, "INDIANI", 4) == 0)
                {
                    msg = indians(cplayer, targetcard, bang);
                }
                else if (strncmp(targetcard->_name, "GATLING", 4) == 0)
                {
                    msg = gatling(cplayer, targetcard, bang);
                }
                else if (strncmp(targetcard->_name, "SALOON", 4) == 0)
                {
                    msg = saloon(cplayer, targetcard, bang);
                }
                // Equip
                else if (strncmp(targetcard->_skill, "Equipment", 4) == 0)
                {
                    equip(cplayer, targetcard, target, bang);
                    // todo: bool -> char*
                }
                else
                {
                    printf("Warning: No valid action.\n");
                }
                // saveLog(msg);
            }
        }

        printf("Turn %d end.\n", total_turn);
        winner = isGameEnd(bang);
        if (winner)
        {
            printf("GAME end. (total turn: %d)\n", total_turn);
            break;
        }
        do {
            bang->_turn = (bang->_turn + 1) % bang->_total_player_cnt;
        } while (isDead(bang->_player[bang->_turn]));
    }
    return winner;
}
/*
need to check
    字串數字 buffer choice buffer 更改
    棄牌堆 to 牌堆
    某個陣營贏
    bang 的次數（無限） v 
    確認每張牌
    全部回合（目前上限 20） v
    // have dead player cards
    if (strncmp(me->_role->_name, "VultureSam", 10) == 0)
    {
        for(int32_t i = 0; i < dead->_hanc_cnt; i++)
        {
            drawplayer(me, dead, 2);
        }
        for(int32_t i = 0; i < 5; i++)
        {
            drawplayer(me, dead, 1);
        }
    }
    // unlimit bang
    if (strncmp(cplayer->_role->_name, "WillyTheKid", 11) == 0 || cplayer)
    {
    }
*/
int32_t getOption(game *bang, player *p)
{
    int32_t want = -2;
    while (want < -1 || want > p->_hand_cnt || want == 0)
    {
        printf("---------------------\n");
        for (int i = 0; i < bang->_total_player_cnt; ++i)
        {
            if(bang->_player[i]->_hp <= 0) continue;
            printf("%s", bang->_player[i]->_name);
            if (strncmp(bang->_player[i]->_identity, "Sceriffo", 4) == 0)
                printf("🚔");
            if (bang->_player[i]->_horse != NULL)
                printf("🐎");
            if(strncmp(bang->_player[i]->_role->_name, "PaulRegret", 5) == 0 ||
               strncmp(bang->_player[i]->_role->_name, "RoseDoolan", 5) == 0)
                printf("(🐎)");
            if (bang->_player[i]->_dinamite != NULL)
                printf("💣");
            if (bang->_player[i]->_jail != NULL)
                printf("⛓️ ");
            if (bang->_player[i]->_barrel != NULL)
                printf("🛢️ ");
            if(strncmp(bang->_player[i]->_role->_name, "Jourdonnais", 5) == 0)
                printf("(🛢️ )");
            if (bang->_player[i]->_gun != NULL)
                if (strncmp(bang->_player[i]->_gun->_name, "VOLCANIC", 4) == 0)
                printf("∞");
            if(strncmp(bang->_player[i]->_role->_name, "WillyTheKid", 11) == 0)
                printf("(∞)");
            if (bang->_player[i]->_gun != NULL)
                printf("🔫");
            int32_t tep_d, tem = 0;
            if (bang->_player[i]->_position == p->_position)
                printf(BLU "(YOU)" RESET);
            else{
                checkDistance(&tep_d, &tem, p, bang->_player[i], bang);
                printf("(d:%d)", tep_d);
            }
            printf("(⁍%d🃏%d) ", bang->_player[i]->_hp, bang->_player[i]->_hand_cnt); // ♡
        }
        printf("\n");
        if (p->_id == 0)
        {
            printf("What do you want to do?\n");
            printf("-1: End turn.\n");
            displayHandCard(p);
            printf("---------------------\nYour Choice " YEL "> " RESET);
            char order[256] = {0};
            char *tmp;
            tmp = calloc(4100, sizeof(char));
            fgets(order, sizeof(order), stdin);
            fflush(stdin);
            want = strtol(order, &tmp, 10);
            // scanf("%d", &want);
        }
        else
        {
            printf("%s's Choice " BLU "> " RESET, p->_name);
            srand( time(NULL) );
            while(want == 0 || want <= -2){
                want = (rand() % (p->_hand_cnt + 2)) -1;
            }
            printf("%d\n", want);
            msleep((1+(rand() % 3))*300);
        }
    }
    return want;
}

int32_t getAction(game *bang, card *c)
{
    int32_t want = -2;

    if (bang->_player[bang->_turn]->_id == 0)
    {
        // -2 返回, -1 丟掉, 自己用/對所有人用, 對特定人用
        printf("---------------------\n");
        printf("Card " YEL "%s" RESET " info:\n%s\n", c->_name, c->_skill);
        printf("---------------------\n");
        printf("-2: Return to your handcard.\n");
        printf("-1: Move to trash.\n");
        if (strncmp("Action:", c->_skill, 7) == 0 ||
            strncmp("PRIGIONE", c->_name, 8) == 0)
        {
            for (int i = 0; i < bang->_total_player_cnt; ++i)
            {
                if (isDead(bang->_player[i]))
                    continue;
                printf("%d: Use the card to %s", i, bang->_player[i]->_name);
                if (i == bang->_turn)
                    printf(BLU" yourself"RESET);
                printf("\n");
            }
        }
        else
        {
            printf("0: Use/Equip this card.\n");
        }
        printf("---------------------\nYour Action " YEL "> " RESET);
        char order[256] = {0};
        char *tmp;
        tmp = calloc(4100, sizeof(char));
        fflush(stdin);
        fgets(order, sizeof(order), stdin);
        fflush(stdin);
        want = strtol(order, &tmp, 10);
        // scanf("%d", &want);
    }
    else
    {
        printf("---------------------\n%s's Action " BLU "> " RESET, bang->_player[bang->_turn]->_name);
        want = (rand() % (bang->_total_player_cnt + 3)) - 2;
        if ((strncmp("Action:", c->_skill, 7) != 0 &&
             strncmp("PRIGIONE", c->_name, 8) != 0)){
            if(want > 0) want = 0;
        }
        else{
            /*
            if(want > 0){
                while(bang->_player[want]->_hp <= 0 || want == bang->_turn)
                    want = (rand() % (bang->_total_player_cnt + 1));
            }
            */
        }
        printf("%d\n", want);
        msleep((1+(rand() % 3))*300);
    }
    if ((strncmp("Action:", c->_skill, 7) == 0 ||
         strncmp("PRIGIONE", c->_name, 8) == 0))
    {
        if (want < -2 || want >= bang->_total_player_cnt)
        {
            printf("Your action is illegal. Try again.\n");
            return -2;
        }
        if (want >= 0)
        {
            if (isDead(bang->_player[want]))
            {
                printf("This player is dead. Try again.\n");
                return -2;
            }
        }
        return want;
    }
    else
    {
        if (want < -2 || want > 0)
        {
            printf("Your action is illegal. Try again.\n");
            return -2;
        }
        if (want == 0)
            want = bang->_turn;
        return want;
    }
}

int32_t shuffingame[MAX_CARD_CNT] = {0};
void shuffle(game *bang)
{
    for (int32_t i = 0; i < bang->_discard_cnt; i++)
    {    
        shuffingame[i] = i;
    }
    int32_t x = 0;
    /*
    printf("shuffle start: %d, %d\n", bang->_discard_cnt, bang->_deck_cnt);
    for(int i = 0; i < bang->_discard_cnt; ++i){
        printf("%d: %s\n", i, bang->_discard[i]->_name);
    }
    for(int i = 0; i < bang->_deck_cnt; ++i){
        printf("%d: %s\n", i, bang->_deck[i]->_name);
    }
    */
        
    if(bang->_discard_cnt > 1){
        for (int32_t i = bang->_discard_cnt - 1; i >= 1; i--)
        {
            int32_t tempt = 0;
            x = rand() % (i);
            tempt = shuffingame[i];
            shuffingame[i] = shuffingame[x];
            shuffingame[x] = tempt;
            bang->_deck[i] = bang->_discard[shuffingame[i]];
            printf("%s\n", bang->_deck[i]->_name);
        }       

    }
    else{
        printf("Warning: no more card avaliable to shuffle.\n");
    }

    bang->_deck[0] = bang->_discard[shuffingame[0]];
    bang->_deck_cnt = bang->_discard_cnt;
    bang->_discard_cnt = 0;
    /*
    printf("shuffle end: %d, %d\n", bang->_discard_cnt, bang->_deck_cnt);
    for(int i = 0; i < bang->_discard_cnt; ++i){
        printf("%d: %s\n", i, bang->_discard[i]->_name);
    }
    for(int i = 0; i < bang->_deck_cnt; ++i){
        printf("%d: %s\n", i, bang->_deck[i]->_name);
    }
    */

    return;
}
void displayPlayer(const player *p)
{
    printf("Health    : %d/%d\n", p->_hp, p->_max_hp);
    printf("position  : %d\n", p->_position);
    printf("identity  : %s\n", (p->_id == 0 || strncmp(p->_identity, "Sceriffo", 4) == 0 ? p->_identity : "TOP SECRET"));
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
        strcat(printmessage, "SUCCESS: ");
    }
    else if (type == 2)
    {
        strcat(strmessage, "FAILED: ");
        strcat(printmessage, "FAILED: ");
    }
    else if (type == 3 || type == 5 || type == 7)
    {
        strcat(strmessage, "Action: ");
        strcat(printmessage, "Action: ");
    }
    else if (type == 4 || type == 6 || type == 8)
    {
        strcat(strmessage, "Warning: ");
        strcat(printmessage, "Warning: ");
    }
    if (type != 9)
    {
        // strcat(strmessage, "Player ");
        // strcat(printmessage, "Player ");
        strcat(strmessage, p->_name);
        strcat(printmessage, p->_name);
    }
    if (type != 5 && type != 6 && type != 7 && type != 8 && type != 9 && type != 0)
    {
        if (type == 3 || type == 4)
        {
            strcat(strmessage, " used ");
            strcat(printmessage, " used ");
        }
        else if (type == 1 || type == 2)
        {
            strcat(strmessage, " judged ");
            strcat(printmessage, " judged ");
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
    if(type == 0)
    {
        strcat(strmessage, "judged");
        strcat(printmessage, "judged");        
    }
    if (type == 1 || type == 3)
    {
        strcat(strmessage, " successed");
        strcat(printmessage, " successed");
    }
    else if (type == 2 || type == 4 || type == 0)
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
    // printf("Judge in\n");
    draw(p, game);
    // printf("draw\n");
    char msg[200] = {0};
    card *jc = p->_hand[p->_hand_cnt - 1]; //Judge card
    // printf("%s\n", jc->_name);
    strcat(msg, jc->_name);
    strcat(msg, ": ");
   //  printf("switch\n");
    switch (jc->_suit)
    {
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
    // printf("tempt\n");
    char tempt[2] = {0};
    tempt[0] = p->_hand[p->_hand_cnt - 1]->_number / 10 + '0';
    strcat(msg, tempt);
    tempt[0] = p->_hand[p->_hand_cnt - 1]->_number % 10 + '0';
    strcat(msg, tempt);
    printf("%s\n", msg);
    saveLog(msg);
    // ♠♥♦♣
    // printf p->_hand[p->_hand_cnt - 1]
    // printf("start Judge\n");
    if (strncmp("BARREL", c->_name, 6) == 0)
    {
        if (p->_hand[p->_hand_cnt - 1]->_suit == 2)
        {
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            changeHP(p, 1, game);
            return displayAction(p, c, 1); // "SUCCESS: " [0] = 'S'
        }
        else
        {
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            return displayAction(p, c, 2); // "FAILED: " [0] = 'F'
        }
    }
    else if (strncmp("PRIGIONE", c->_name, 8) == 0)
    {
        if (p->_hand[p->_hand_cnt - 1]->_suit == 2)
        {
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            discard(p, c, 1, game);
            return displayAction(p, c, 1);
        }
        else
        {
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            discard(p, c, 1, game);
            return displayAction(p, c, 2);
        }
    }
    else if (strncmp("DINAMITE", c->_name, 8) == 0)
    {
        if (p->_hand[p->_hand_cnt - 1]->_suit == 1 && (p->_hand[p->_hand_cnt - 1]->_number >= 2 && p->_hand[p->_hand_cnt - 1]->_number <= 9))
        {
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            changeHP(p, -3, game);
            discard(p, c, 1, game);
            // printf("return dinamite\n");
            return displayAction(p, c, 1);
        }
        else
        {
            int32_t next_man = game->_turn;
            do {
                next_man = (next_man + 1) % game->_total_player_cnt;
            } while (isDead(game->_player[next_man]));
            game->_player[next_man]->_dinamite = c;
            p->_dinamite = NULL;
            discard(p, p->_hand[p->_hand_cnt - 1], 2, game);
            // printf("return dinamite\n");
            return displayAction(p, c, 2);
        }
    }
    else
    {
        // printf("return 0\n");
        return displayAction(p, c, 0);
    }
    // printf("return 0\n");
    return displayAction(p, c, 0);
}