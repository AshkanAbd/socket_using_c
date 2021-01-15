#include "client.h"

void change_max(int max) {
    MAX = max;
}

void init_client(Client *c, int buffer_size, int socket) {
    c->socket = socket;
    c->buffer_size = buffer_size;
}
