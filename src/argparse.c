#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "version.h"
#include "errors.h"

void help_msg(void);

char* port = NULL;

void parse_args(int* argc, char* argv[]) {
    if(*argc < 2) {
        help_msg();
        exit(EXIT_SUCCESS);
    };

    int opt = 0;

    static struct option argument_options[] = {
        {"server", no_argument, 0, 's'},
        {"help", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(*argc, argv, "p:sh", argument_options, NULL)) != -1) {
        switch(opt) {
            case 's':
                break;
            case 'p':
                if(assert_port(optarg, "port") == -1) {
                    
                    exit(EXIT_FAILURE);
                }

                port = optarg;
                break;
            
            case 'h':
            default:
                help_msg();
                exit(EXIT_SUCCESS);
                break;
        }
    }
}

void help_msg(void) {
    printf(
        "%s - commandline file sharing [version %s]\n\n"
        "Usage:\t%s [options] [file...] [destination]\n",
        PROG_NAME, PROG_VERSION, PROG_NAME
    );
}