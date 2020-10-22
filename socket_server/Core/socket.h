#ifndef SOCKET_SERVER_SOCKET_H
#define SOCKET_SERVER_SOCKET_H

#include <errno.h>
#include <winsock2.h>
#include <io.h>

#define SA struct sockaddr

struct Socket {
    int socket_fd, connection_fd, len;
    struct sockaddr_in server_address, server_cli;
};

int create_socket(struct Socket *s);

void assign_port(struct Socket *s, int port);

int bind_socket(struct Socket *s);

int listen_socket(struct Socket *s);

int accept_connection(struct Socket *s);

void close_socket(struct Socket *s);

#endif //SOCKET_SERVER_SOCKET_H
