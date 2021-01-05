#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>

typedef struct Client Client;

struct Client {
    int *socket;
};

void init_client(Client *c, int *socket);

void close_client(Client *c);

#endif //SOCKET_SERVER_CLIENT_H