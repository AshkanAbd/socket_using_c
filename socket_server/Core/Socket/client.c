#include <io.h>
#include "client.h"

void init_client(Client *c, int *socket) {
    c->socket = malloc(sizeof(int));
    memset(c->socket, 0, sizeof(int));
    memcpy(c->socket, socket, sizeof(int));
}

void close_client(Client *c) {
    close(*c->socket);
    free(c);
}