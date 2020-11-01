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

void set_message_func(struct Client *c, void (*message_func)(struct Client *, char *)) {
    c->message_func = message_func;
}

void set_connect_func(struct Client *c, void (*connect_func)(struct Client *)) {
    c->connect_func = connect_func;
}

void set_disconnect_func(struct Client *c, void (*disconnect_func)(struct Client *)) {
    c->disconnect_func = disconnect_func;
}


void start_client(struct Client *c) {
    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_func, c);
}

void *receive_func(void *obj) {
    struct Client *c = (struct Client *) obj;
    if (c->connect_func != NULL) {
        (*c->connect_func)(c);
    }

    while (1) {
        memset(c->buffer, 0, c->buffer_size);
        recv(*c->socket, c->buffer, c->buffer_size, 0);

        if (!(strlen(c->buffer) == 1 && *c->buffer == '\n') && strlen(c->buffer) != 0) {
            if (c->message_func != NULL) {
                (*c->message_func)(c, c->buffer);
            }
        } else if (strlen(c->buffer) == 0) {
            printf("%d disconnected\n", *c->socket);
            if (c->disconnect_func != NULL) {
                (*c->disconnect_func)(c);
            }
            close(*c->socket);
            return 0;
        }
    }
}