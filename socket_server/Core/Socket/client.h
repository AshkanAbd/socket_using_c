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

void set_message_func(struct Client *c, void (*message_func)(struct Client *, char *));

void set_connect_func(struct Client *c, void (*connect_func)(struct Client *));

void set_disconnect_func(struct Client *c, void (*disconnect_func)(struct Client *));

void start_client(struct Client *c);

void *receive_func(void *obj);

#endif //SOCKET_SERVER_CLIENT_H