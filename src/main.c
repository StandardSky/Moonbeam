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
#include "log.h"
#include "argparse.h"

int main(int argc, char* argv[]) {
    parse_args(&argc, argv);

    struct addrinfo *serv_info = NULL;
    int sock_fd = 0;

    // redo args in a better way later
    if(strcmp(argv[1], "server") == 0) {

        if(setup_server(&serv_info, &sock_fd) != 0) return EXIT_FAILURE;

        while(1) {
            int incoming_sock_fd = 0;
            struct sockaddr_storage incoming_addr = {0};
            socklen_t incoming_addr_size = sizeof(incoming_addr);

            if(assert_syscall(incoming_sock_fd = accept(sock_fd, (struct sockaddr*)&incoming_addr, &incoming_addr_size), "accept") == -1) return ERR_ACCEPT;

            close(incoming_sock_fd);
        }

    }

    close(sock_fd);
    freeaddrinfo(serv_info);
    return 0;
}