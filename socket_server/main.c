#include "Core/server_socket.h"
#include "Core/client.h"

#define MAX 1024
#define PORT 8080

void on_message_received(struct Client *c, char *msg);

void on_client_connect(struct Client *c);

void on_client_disconnect(struct Client *c);

struct Client *clients;
int clientIndex = 0;

int main() {
    struct ServerSocket server_socket;
    int error;
    clients = malloc(MAX * sizeof(struct Client));
    memset(clients, 0, MAX * sizeof(struct Client));

    if ((error = create_socket(&server_socket)) != 0) {
        printf("Failed to create socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket created...\n");
    }

    assign_port(&server_socket, PORT);

    if ((error = bind_socket(&server_socket)) != 0) {
        printf("Fail to bind socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Socket bound...\n");
    }

    if ((error = listen_socket(&server_socket)) != 0) {
        printf("Failed to listen socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Start to listen...\n");
    }

    while (1) {
        int connection = accept_connection(&server_socket);
        printf("connected %d\n", connection);
        if (connection < 0) {
            printf("Failed to accept connection\n");
            printf("Error= %d:%s\n", connection, strerror(connection));
        } else {
            struct Client *client = (clients + clientIndex++);
            init_client(client, MAX, &connection);
            set_message_func(client, on_message_received);
            set_connect_func(client, on_client_connect);
            set_disconnect_func(client, on_client_disconnect);
            start_client(client);
        }
    }
}

void on_message_received(struct Client *c, char *msg) {
    struct Client *client;
    for (int i = 0; i < clientIndex; ++i) {
        client = (clients + i);

        if (client->socket != c->socket) {
            char *msg_with_name = malloc(strlen(c->client_name) + strlen(msg) + 3);
            memset(msg_with_name, 0, strlen(c->client_name) + strlen(msg) + 3);
            memcpy(msg_with_name, c->client_name, strlen(c->client_name));
            *(msg_with_name + strlen(c->client_name)) = ':';
            *(msg_with_name + strlen(c->client_name) + 1) = ' ';
            memcpy(msg_with_name + strlen(c->client_name) + 2, msg, strlen(msg));

            send(*client->socket, msg_with_name, (int) strlen(msg_with_name), 0);
        }
    }
}

void on_client_connect(struct Client *c) {
    struct Client *client;
    char *msg = " connected\n";
    for (int i = 0; i < clientIndex; ++i) {
        client = (clients + i);

        if (client->socket != c->socket) {
            char *msg_with_name = malloc(strlen(c->client_name) + strlen(msg) + 1);
            memset(msg_with_name, 0, strlen(c->client_name) + strlen(msg) + 1);
            memcpy(msg_with_name, c->client_name, strlen(c->client_name));
            memcpy(msg_with_name + strlen(c->client_name), msg, strlen(msg));

            send(*client->socket, msg_with_name, (int) strlen(msg_with_name), 0);
        }
    }
}

void on_client_disconnect(struct Client *c) {
    struct Client *client;
    char *msg = " disconnected\n";
    for (int i = 0; i < clientIndex; ++i) {
        client = (clients + i);

        if (client->socket != c->socket) {
            char *msg_with_name = malloc(strlen(c->client_name) + strlen(msg) + 1);
            memset(msg_with_name, 0, strlen(c->client_name) + strlen(msg) + 1);
            memcpy(msg_with_name, c->client_name, strlen(c->client_name));
            memcpy(msg_with_name + strlen(c->client_name), msg, strlen(msg));

            send(*client->socket, msg_with_name, (int) strlen(msg_with_name), 0);
        }
    }
}