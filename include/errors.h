#ifndef ERROR_CODE_H
#define ERROR_CODE_H

enum {
    ERR_GETADDRINFO = 1001,
    ERR_SOCKET = 1002,
    ERR_BIND = 1003,
    ERR_LISTEN = 1004,
    ERR_ACCEPT = 1005,
    ERR_PORT = 2001,
};

int assert_syscall(int return_code, const char* fail_msg);
int assert_gai(int return_code, const char* fail_msg);
int assert_port(char* port, const char* fail_smg);

#endif