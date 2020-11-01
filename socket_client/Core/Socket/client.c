#include "client.h"

void init_client(struct Client *c, int buffer_size, int socket) {
    c->socket = socket;
    c->buffer_size = buffer_size;
}
