#ifndef SOCKET_CLIENT_CLIENT_SOCKET_H
#define SOCKET_CLIENT_CLIENT_SOCKET_H

#include <string.h>
#include <winsock2.h>
#include <io.h>

#define SA struct sockaddr

struct ClientSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

int create_socket(struct ClientSocket *s);

void assign_port(struct ClientSocket *s, char *ip, int port);

int connect_socket(struct ClientSocket *s);

void close_socket(struct ClientSocket *s);

#endif //SOCKET_CLIENT_CLIENT_SOCKET_H
