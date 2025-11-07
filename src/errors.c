#include <netdb.h>
#include <stdio.h>

#include "errors.h"

int assert_code(int return_code, const char* fail_msg) {
    if(return_code == 0) return 0;
    if(return_code == -1) {
        perror(fail_msg);
        return -1;
    };

    fprintf(stderr, "%s: %s\n", fail_msg, gai_strerror(return_code));

    return 0;
}