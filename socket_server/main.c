#include "Core/Socket/server_socket.h"
#include "Core/Socket/client.h"
#include "Core/Pipeline/pipeline.h"

#define MAX 1024
#define PORT 8080

void on_message_received(struct Client *c, char *msg);

void on_client_connect(struct Client *c);

void on_client_disconnect(struct Client *c);

struct Client *clients;
int clientIndex = 0;

void init_server(struct ServerSocket *server_socket);

int main() {
    struct ServerSocket server_socket;
    struct Pipeline pipeline;

    clients = malloc(MAX * sizeof(struct Client));
    memset(clients, 0, MAX * sizeof(struct Client));

    init_server(&server_socket);
    init_pipeline(&pipeline);

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

void init_server(struct ServerSocket *server_socket) {
    int error;
    if ((error = create_socket(server_socket)) != 0) {
        printf("Failed to create socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket created...\n");
    }

    assign_port(server_socket, PORT);

    if ((error = bind_socket(server_socket)) != 0) {
        printf("Fail to bind socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Socket bound...\n");
    }

    if ((error = listen_socket(server_socket)) != 0) {
        printf("Failed to listen socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Start to listen...\n");
    }

}

void on_message_received(struct Client *c, char *msg) {

}

void on_client_connect(struct Client *c) {

}

void on_client_disconnect(struct Client *c) {

}