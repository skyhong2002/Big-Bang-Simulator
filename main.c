#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "code/bang.h"

int main(int32_t argc, char* argv[])
{
    char *yourname = "Joker";
    char logfile_name[FILENAME_MAX] = "log.txt";
    int32_t playercnt = 4;

    int c;
    const char* short_opt = "o:p:n:h";
    struct option long_opt[] = {
        { "output", required_argument, NULL, 'o' },
        { "player", required_argument, NULL, 'p' },
        { "name", required_argument, NULL, 'n' },
        { "help", no_argument, NULL, 'h' },
        { 0, 0, NULL, 0 } /* end-of-array marker */
    };
    while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        char* endp = NULL;
        long l = -1;
        switch (c) {
		case 'o':
			strcpy(logfile_name, optarg);
            break;
        case 'n':
			strcpy(yourname, optarg);
        break;
		case 'p':
            if (!optarg ||  ((l=strtol(optarg, &endp, 10)),(endp && *endp))){ 
                fprintf(stderr, "invalid p option %s - expecting a number\n", optarg?optarg:"");
                exit(EXIT_FAILURE);
            };
            if (l < 4 || l > 7){ 
                fprintf(stderr, "invalid p option %s - number should between 4~7\n", optarg?optarg:"");
                exit(EXIT_FAILURE);
            };
            playercnt = l;
            break;
        case 'h':
		default:
            fprintf(stderr,
                "Usage:\n" 
				"  %s [options]\n"
				"    -o, --output: Output file name. default: log.txt\n"
				"    -n, --name  : Your name. default: Joker\n"
				"    -p, --player: Number of Player. default: 4 (4~7)\n"
				"    -h, --help  : This description\n"
                "\n",
                argv[0]);
			exit(0);
        }
    }
    //option
    printf( "==========================\n"
            "    Big Bang Simulator    \n"
            MAG"(う-`)づ"YEL"︻╦̵̵̿╤──"BLU"   \\(˚☐˚」)/\n"RESET
            "    Created by Team 10    \n"
            "==========================\n\n");
    game bang;
    gameInit(&bang, playercnt, yourname, logfile_name);

    gameloop(&bang);
    return 0;
}
