#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "errors.h"

const int BACKLOG = 5;

int setup_server(struct addrinfo** serv_info, int* sock_fd) {
    struct addrinfo hints = {0};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = 0;
    
    if (assert_gai((status = getaddrinfo(NULL, "6543", &hints, serv_info)), "addrinfo") == -1) return ERR_GETADDRINFO;
    if (assert_syscall((*sock_fd = socket((*serv_info)->ai_family, (*serv_info)->ai_socktype, (*serv_info)->ai_protocol)), "socket") == -1) return ERR_SOCKET;
    if(assert_syscall(bind(*sock_fd, (*serv_info)->ai_addr, (*serv_info)->ai_addrlen), "bind") == -1) return ERR_BIND;
    if(assert_syscall(listen(*sock_fd, BACKLOG), "listen") == -1) return ERR_LISTEN;

    return 0;
}