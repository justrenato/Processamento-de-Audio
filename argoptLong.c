#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

struct option longopts[] = {
    {"list",   optional_argument, 0, 'l'},
    {"touch",  required_argument, 0, 'm'},
    {"rm",     required_argument, 0, 'r'},
    {"date",   no_argument,       0, 'd'}
};

int main (int argc, char **argv) {
    int i, ch, indexptr = 0;
    char str[100];
    opterr = 0;
    while ((ch = getopt_long(argc, argv, "l::m:r:d", longopts, &indexptr)) != -1){
        switch (ch) {
            case 'd':
                printf("short option - %c  long option - %s\n",ch, longopts[indexptr].name);
                system("date");
                break;
            case 'l':
                printf("short option - %c  long option - %s\n",ch, longopts[indexptr].name);
                strcpy(str, "ls -l ");
                if (optarg)strcat(str, optarg);
                system(str);
                break;
            case 'm':
                printf("short option - %c  long option - %s\n",ch, longopts[indexptr].name);
                strcpy(str, "touch ");
                strcat(str, optarg);
                system(str);
                break;
            case 'r':
                printf("short option - %c  long option - %s\n",ch, longopts[indexptr].name);
                strcpy(str, "rm ");
                strcat(str, optarg);
                system(str);
                break;
            case '?':
                if (optopt == 'r' || optopt == 'm')
                        printf("Argument is mandatory for --%s\n",
                                longopts[indexptr].name);
                else if (isprint (optopt))
                        printf("U have given an unknown option - %c\n",
                                        optopt);
                else
                        printf("Unknown Error-0x%08x\n", optopt);
                break;
            default:
                exit(0);
        }
    }
    for (i = optind; i < argc; i++)
        printf("Redundant argument - %s\n", argv[i]);
    return 0;
}