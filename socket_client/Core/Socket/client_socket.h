#ifndef SOCKET_CLIENT_CLIENT_SOCKET_H
#define SOCKET_CLIENT_CLIENT_SOCKET_H

#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include <io.h>

typedef ClientSocket ClientSocket;

ClientSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

int create_socket(ClientSocket *s);

void assign_port(ClientSocket *s, char *ip, int port);

int connect_socket(ClientSocket *s);

void close_socket(ClientSocket *s);

void init_socket(ClientSocket *client_socket, char *ip, int port);


#endif //SOCKET_CLIENT_CLIENT_SOCKET_H
