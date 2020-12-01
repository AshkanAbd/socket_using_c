#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <winsock2.h>
#include <pthread.h>

#define MAX 1024

struct Client {
    int socket, buffer_size;
};

void init_client(struct Client *c, int buffer_size, int socket);

#endif //SOCKET_SERVER_CLIENT_H
