#include "client.h"

void init_client(struct Client *c, int buffer_size, int socket) {
    c->buffer = malloc(buffer_size);
    memset(c->buffer, 0, buffer_size);

    c->client_name = malloc(buffer_size);
    memset(c->client_name, 0, buffer_size);

    c->socket = socket;
    c->buffer_size = buffer_size;
}

int set_name(struct Client *c) {
    int counter = 0;
    do {
        printf("Enter your name:");
        while ((*(c->client_name + counter++) = (char) getchar()) != '\n');
    } while (strcmp(c->client_name, "\n") == 0);

    send(c->socket, c->client_name, c->buffer_size, 0);
}

void start_client(struct Client *c) {
    set_name(c);

    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_func, c);
    pthread_t send_thread;
    pthread_create(&send_thread, NULL, send_func, c);
    while (1);
}

void *receive_func(void *obj) {
    struct Client *c = (struct Client *) obj;

    while (1) {
        memset(c->buffer, 0, c->buffer_size);
        recv(c->socket, c->buffer, c->buffer_size, 0);

        if (!(strlen(c->buffer) == 1 && *c->buffer == '\n') && strlen(c->buffer) != 0) {
            printf("%s", c->buffer);
        }
    }
}

void *send_func(void *obj) {
    struct Client *c = (struct Client *) obj;
    int counter = 0;

    while (1) {
        memset(c->buffer, 0, c->buffer_size);
        counter = 0;
        while ((*(c->buffer + counter++) = (char) getchar()) != '\n');

        if (strlen(c->buffer) != 0) {
            send(c->socket, c->buffer, c->buffer_size, 0);
        }
    }
}
