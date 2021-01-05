#ifndef SOCKET_SERVER_SERVER_SOCKET_H
#define SOCKET_SERVER_SERVER_SOCKET_H

#include <errno.h>
#include <winsock2.h>
#include <io.h>

typedef struct ServerSocket ServerSocket;

struct ServerSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

int create_socket(ServerSocket *s);

void assign_port(ServerSocket *s, int port);

int bind_socket(ServerSocket *s);

int listen_socket(ServerSocket *s);

int accept_connection(ServerSocket *s);

void close_socket(ServerSocket *s);

#endif //SOCKET_SERVER_SERVER_SOCKET_H
