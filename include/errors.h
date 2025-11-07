#ifndef ERROR_CODE_H
#define ERROR_CODE_H

enum {
    ERR_GETADDRINFO = 1001,
    ERR_SOCKET = 1002,
    ERR_BIND = 1003,
    ERR_LISTEN = 1004,
    ERR_ACCEPT = 1005
};

int assert_code(int return_code, const char* fail_msg);

#endif