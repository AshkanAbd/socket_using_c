#ifndef SOCKET_CLIENT_CLIENT_SOCKET_H
#define SOCKET_CLIENT_CLIENT_SOCKET_H

#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include <io.h>

#define PORT 8080

struct ClientSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

int create_socket(struct ClientSocket *s);

void assign_port(struct ClientSocket *s, char *ip, int port);

int connect_socket(struct ClientSocket *s);

void close_socket(struct ClientSocket *s);

void init_socket(struct ClientSocket *client_socket);


#endif //SOCKET_CLIENT_CLIENT_SOCKET_H
