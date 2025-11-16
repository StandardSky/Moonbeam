#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

int assert_syscall(int return_code, const char* fail_msg) {
    if(return_code == -1) {
        perror(fail_msg);

        return -1;
    };

    return 0;
}

int assert_gai(int return_code, const char* fail_msg) {
    if(return_code != 0) {
        fprintf(stderr, "%s: %s\n", fail_msg, gai_strerror(return_code));

        return -1;
    }

    return 0;
}

int assert_port(char* port, const char* fail_msg) {
    char* endptr = NULL;
    long int parsed_port = strtol(port, &endptr, 10);

    if((endptr != port && (*endptr == '\0')) && (parsed_port > 1023 && parsed_port < 65536)) return 0;

    fprintf(stderr, "%s: invalid port provided\n", fail_msg);

    return -1;
}