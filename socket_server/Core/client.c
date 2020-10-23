#include <io.h>
#include "client.h"

void init_client(struct Client *c, int buffer_size, int *socket) {
    c->buffer = malloc(buffer_size);
    memset(c->buffer, 0, buffer_size);

    c->client_name = malloc(buffer_size);
    memset(c->client_name, 0, buffer_size);

    c->socket = malloc(sizeof(int));
    memset(c->socket, 0, sizeof(int));
    memcpy(c->socket, socket, sizeof(int));

    c->buffer_size = buffer_size;
}

int set_name(struct Client *c) {
    char *empty_name_error = "Name is cannot be empty\n";

    recv(*c->socket, c->client_name, c->buffer_size, 0);
    if (strlen(c->client_name) == 0) {
        close(*c->socket);
        return 1;
    }
    while (strcmp(c->client_name, "\n") == 0) {
        send(*c->socket, empty_name_error, (int) strlen(empty_name_error), 0);
        memset(c->client_name, 0, c->buffer_size);
        recv(*c->socket, c->client_name, c->buffer_size, 0);
    }
    *(c->client_name + strlen(c->client_name) - 1) = 0;
    return 0;
}

void set_message_func(struct Client *c, void (*message_func)(struct Client *, char *)) {
    c->message_func = message_func;
}

void start_client(struct Client *c) {
    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_func, c);
}

void *receive_func(void *obj) {
    struct Client *c = (struct Client *) obj;

    if (set_name(c) != 0) {
        return 0;
    }

    int disconnectThreshold = 0;
    while (1) {
        memset(c->buffer, 0, c->buffer_size);
        recv(*c->socket, c->buffer, c->buffer_size, 0);

        if (!(strlen(c->buffer) == 1 && *c->buffer == '\n') && strlen(c->buffer) != 0) {
            disconnectThreshold = 0;
            (*c->message_func)(c, c->buffer);
        } else if (strlen(c->buffer) == 0) {
            disconnectThreshold++;
            if (disconnectThreshold >= 5) {
                printf("%d disconnected\n", *c->socket);
                close(*c->socket);
                return 0;
            }
        }
    }
}
