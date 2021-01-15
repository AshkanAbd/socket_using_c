#include "client_socket.h"

int create_socket(ClientSocket *s) {
    WSADATA Data;
    WSAStartup(MAKEWORD(2, 2), &Data);

    s->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s->socket_fd == -1) {
        return errno;
    }
    memset(&(s->server_address), 0, sizeof(s->server_address));
    return 0;
}

void assign_port(ClientSocket *s, char *ip, int port) {
    s->server_address.sin_family = AF_INET;
    s->server_address.sin_addr.s_addr = inet_addr(ip);
    s->server_address.sin_port = htons(port);
}

int connect_socket(ClientSocket *s) {
    if (connect(s->socket_fd, (struct sockaddr *) &s->server_address, sizeof(s->server_address)) != 0) {
        return 1;
    }
    return 0;
}

void close_socket(ClientSocket *s) {
    close(s->socket_fd);
    WSACleanup();
}

void init_socket(ClientSocket *client_socket, char *ip, int port) {
    int error;

    if ((error = create_socket(client_socket) != 0)) {
        printf("Failed to create socket\n");
        printf("Error= %d: %s\n", error, strerror(error));
        exit(1);
    }

    assign_port(client_socket, ip, port);

    if ((error = connect_socket(client_socket) != 0)) {
        printf("Failed to connect\n");
        printf("Error= %d: %s\n", error, strerror(error));
        exit(1);
    }
}
