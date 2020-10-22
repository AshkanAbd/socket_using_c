#ifndef SOCKET_SERVER_SERVER_SOCKET_H
#define SOCKET_SERVER_SERVER_SOCKET_H

#include <errno.h>
#include <winsock2.h>
#include <io.h>

#define SA struct sockaddr

struct ServerSocket {
    int socket_fd, connection_fd, len;
    struct sockaddr_in server_address, server_cli;
};

int create_socket(struct ServerSocket *s);

void assign_port(struct ServerSocket *s, int port);

int bind_socket(struct ServerSocket *s);

int listen_socket(struct ServerSocket *s);

int accept_connection(struct ServerSocket *s);

void close_socket(struct ServerSocket *s);

#endif //SOCKET_SERVER_SERVER_SOCKET_H
