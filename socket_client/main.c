#include "Core/Socket/client_socket.h"
#include "Core/Socket/client.h"

#define MAX 1024
#define PORT 8080

void init_socket(struct ClientSocket *client_socket);

void send_request(struct Client *client);

int main() {
    struct ClientSocket client_socket;
    struct Client client;

    init_socket(&client_socket);

    init_client(&client, MAX, client_socket.socket_fd);
    send_request(&client);
}

void init_socket(struct ClientSocket *client_socket) {

    int error;

    if ((error = create_socket(client_socket) != 0)) {
        printf("Failed to create socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket created...\n");
    }

    assign_port(client_socket, "127.0.0.1", PORT);

    if ((error = connect_socket(client_socket) != 0)) {
        printf("Failed to connect\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket connected...\n");
    }
}
