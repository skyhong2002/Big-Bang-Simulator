#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #include "code/game.h"
// #include "code/player.h"
#include "code/bang.h"
// #include "code/role.h"

int main()
{
    char *yourname = "John Doe";
    int32_t playercnt = 4;

    //option
    printf("BANG!\n");
    game bang;
    gameInit(&bang, playercnt, yourname);
    // gameloop(&bang);
    return 0;
}
