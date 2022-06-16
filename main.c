#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>

#include "code/bang.h"

int main()
{
    char *yourname = "John Doe";
    int32_t playercnt = 4;

    //option
    printf( "==========================\n"
            "    Big Bang Simulator    \n"
            MAG"(う-`)づ"YEL"︻╦̵̵̿╤──"BLU"   \\(˚☐˚」)/\n"RESET
            "    Created by Team 10    \n"
            "==========================\n");
    game bang;
    gameInit(&bang, playercnt, yourname);

    gameloop(&bang);
    return 0;
}
