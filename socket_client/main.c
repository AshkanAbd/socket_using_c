#include "Core/client_socket.h"
#include "Core/client.h"

#define MAX 1024
#define PORT 8080
#define SA struct sockaddr


int main() {
    struct ClientSocket client_socket;
    int error;

    if ((error = create_socket(&client_socket) != 0)) {
        printf("Failed to create socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket created...\n");
    }

    assign_port(&client_socket, "127.0.0.1", PORT);

    if ((error = connect_socket(&client_socket) != 0)) {
        printf("Failed to connect\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket connected...\n");
    }

    struct Client client;
    init_client(&client, MAX, client_socket.socket_fd);
    start_client(&client);
}
