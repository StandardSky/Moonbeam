#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>

#include "version.h"
#include "error_code.h"
#include "log.h"

int setup_server(struct addrinfo**);
void print_arguments(void);

int main(void) {
    struct addrinfo *server_info = NULL;
    
    if(setup_server(&server_info) != 0) {
        return EXIT_FAILURE;
    }

    freeaddrinfo(server_info);
    return 0;
}

int setup_server(struct addrinfo** server_info) {
    struct addrinfo hints = {0};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = 0;

    if((status = getaddrinfo(NULL, "6543", &hints, server_info)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        return ERR_GETADDRINFO;
    }

    int socket_fd = 0;
    if((socket_fd = socket((*server_info)->ai_family, (*server_info)->ai_socktype, (*server_info)->ai_protocol)) == -1) {
        perror("socket");
        return ERR_SOCKET;
    };

    if(bind(socket_fd, (*server_info)->ai_addr, (*server_info)->ai_addrlen) == -1) {
        perror("bind");
        return ERR_BIND;
    }

    if(listen(socket_fd, 1) == -1) {
        perror("listen");
        return ERR_LISTEN;
    };

    log_message("Port bound to 6543, server created\n");

    int incoming_socket_fd = 0;
    socklen_t incoming_addr_size = 0;
    socklen_t addr_size = sizeof(incoming_addr_size);
    if((incoming_socket_fd = accept(socket_fd, (struct sockaddr*)&incoming_addr_size, &addr_size)) == -1) {
        perror("accept");
        return ERR_ACCEPT;
    }

    int yes = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    return 0;
}

void print_arguments(void) {
    printf(
        "%s - commandline p2p file sharing [VERSION %s]\n\n"
        "Usage:\t%s [options] <ip address>\n",
        PROG_NAME, PROG_VERSION, PROG_NAME
    );
}