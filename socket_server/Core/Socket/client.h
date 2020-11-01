#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>

struct Client {
    int *socket;
    int buffer_size;
    char *buffer;

    void (*message_func)(struct Client *, char *);

    void (*connect_func)(struct Client *);

    void (*disconnect_func)(struct Client *);
};

void init_client(struct Client *c, int buffer_size, int *socket);

void close_client(struct Client *c);

#endif //SOCKET_SERVER_CLIENT_H