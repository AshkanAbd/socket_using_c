#include "Core/Socket/server_socket.h"
#include "Core/Socket/client.h"

#define MAX 1024
#define PORT 8080

int main() {
    struct ServerSocket server_socket;
    int error;

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
    if ((error = accept_connection(&server_socket) != 0)) {
        printf("Failed to accept connection\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        struct Client client;
        init_client(&client, MAX, server_socket.connection_fd);
        start_client(&client);
    }
    while (1);
}