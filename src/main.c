#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#include "version.h"
#include "errors.h"
#include "log.h"

#define BACKLOG 1

int setup_server(struct addrinfo**, int*);
void print_arguments(void);

int main(void) {
    struct addrinfo *server_info = NULL;
    int socket_fd = 0;
    
    if(setup_server(&server_info, &socket_fd) != 0) return EXIT_FAILURE;

    freeaddrinfo(server_info);
    return 0;
}

int setup_server(struct addrinfo** server_info, int* socket_fd) {
    struct addrinfo hints = {0};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = 0;

    if(assert_code((status = getaddrinfo(NULL, "6543", &hints, server_info)), "getaddrinfo") == -1) return ERR_GETADDRINFO;

    if(assert_code((*socket_fd = socket((*server_info)->ai_family, (*server_info)->ai_socktype, (*server_info)->ai_protocol)) == -1, "socket") == -1) return ERR_SOCKET;
    if(assert_code((bind(*socket_fd, (*server_info)->ai_addr, (*server_info)->ai_addrlen) == -1), "bind") == -1) return ERR_BIND;
    if(assert_code(listen(*socket_fd, BACKLOG) == -1, "listen") == -1) return ERR_LISTEN;

    int yes = 1;
    setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    return 0;
}

void print_arguments(void) {
    printf(
        "%s - commandline p2p file sharing [VERSION %s]\n\n"
        "Usage:\t%s [options] <ip address>\n",
        PROG_NAME, PROG_VERSION, PROG_NAME
    );
}