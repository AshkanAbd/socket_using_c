#include <io.h>
#include "client.h"

void init_client(struct Client *c, int buffer_size, int *socket) {
    c->buffer = malloc(buffer_size);
    memset(c->buffer, 0, buffer_size);

    c->socket = malloc(sizeof(int));
    memset(c->socket, 0, sizeof(int));
    memcpy(c->socket, socket, sizeof(int));

    c->buffer_size = buffer_size;
}

void close_client(struct Client *c) {
    close(*c->socket);
}