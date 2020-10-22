#include <io.h>
#include "client.h"

void init_client(struct Client *c, int buffer_size, int socket) {
    c->buffer = malloc(buffer_size);
    memset(c->buffer, 0, buffer_size);

    c->client_name = malloc(buffer_size);
    memset(c->client_name, 0, buffer_size);

    c->socket = socket;
    c->buffer_size = buffer_size;
}

void set_name(struct Client *c) {
    char *empty_name_error = "Name is cannot be empty\n";

    recv(c->socket, c->client_name, c->buffer_size, 0);
    if (strlen(c->client_name) == 0) {
        close(c->socket);
        return;
    }
    while (strcmp(c->client_name, "\n") == 0) {
        send(c->socket, empty_name_error, (int) strlen(empty_name_error), 0);
        memset(c->client_name, 0, c->buffer_size);
        recv(c->socket, c->client_name, c->buffer_size, 0);
    }
    *(c->client_name + strlen(c->client_name) - 1) = 0;
    printf("%s connected\n", c->client_name);
}

void start(struct Client *c) {

}