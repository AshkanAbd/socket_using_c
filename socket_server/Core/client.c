#include <io.h>
#include "client.h"

void init_client(struct Client *c, int buffer_size, int socket) {
    c->buffer = malloc(buffer_size);
    memset(c->buffer, 0, buffer_size);

    c->client_name = malloc(buffer_size);
    memset(c->client_name, 0, buffer_size);

    memcpy(&c->socket, &socket, sizeof(int));
    c->buffer_size = buffer_size;
}

int set_name(struct Client *c) {
    char *empty_name_error = "Name is cannot be empty\n";
    char *unknown_error = "An error occurred, please try again\n";
    int socket = c->socket;

    recv(socket, c->client_name, c->buffer_size, 0);
    if (strlen(c->client_name) == 0) {
        send(socket, unknown_error, (int) strlen(unknown_error), 0);
        close(socket);
        return 1;
    }
    while (strcmp(c->client_name, "\n") == 0) {
        send(socket, empty_name_error, (int) strlen(empty_name_error), 0);
        memset(c->client_name, 0, c->buffer_size);
        recv(socket, c->client_name, c->buffer_size, 0);
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

    int socket = c->socket;
    int disconnectThreshold = 0;
    while (1) {
        memset(c->buffer, 0, c->buffer_size);
        recv(socket, c->buffer, c->buffer_size, 0);

        if (!(strlen(c->buffer) == 1 && *c->buffer == '\n') && strlen(c->buffer) != 0) {
            disconnectThreshold = 0;
            (*c->message_func)(c, c->buffer);
        } else if (strlen(c->buffer) == 0) {
            disconnectThreshold++;
            if (disconnectThreshold >= 5) {
                printf("%d disconnected\n", socket);
                close(socket);
                return 0;
            }
        }
    }
}
