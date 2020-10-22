#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <winsock2.h>
#include <pthread.h>

struct Client {
    int socket, buffer_size;
    char *client_name;
    char *buffer;
};

void init_client(struct Client *c, int buffer_size, int socket);

int set_name(struct Client *c);

void start_client(struct Client *c);

void *send_func(void *obj);

void *receive_func(void *obj);

#endif //SOCKET_SERVER_CLIENT_H
