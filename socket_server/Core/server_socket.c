#include "server_socket.h"

int create_socket(struct ServerSocket *s) {
    WSADATA Data;
    WSAStartup(MAKEWORD(2, 2), &Data);

    s->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s->socket_fd == -1) {
        return errno;
    }
    memset(&(s->server_address), 0, sizeof(s->server_address));
    return 0;
}

void assign_port(struct ServerSocket *s, int port) {
    s->server_address.sin_family = AF_INET;
    s->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    s->server_address.sin_port = htons(port);
}

int bind_socket(struct ServerSocket *s) {
    if ((bind(s->socket_fd, (SA *) &(s->server_address), sizeof(s->server_address))) != 0) {
        return errno;
    } else {
        return 0;
    }
}

int listen_socket(struct ServerSocket *s) {
    if ((listen(s->socket_fd, 5)) != 0) {
        return errno;
    }
    return 0;
}

int accept_connection(struct ServerSocket *s) {
    s->connection_fd = accept(s->socket_fd, NULL, NULL);
    if (s->connection_fd < 0) {
        return errno;
    }
    return 0;
}

void close_socket(struct ServerSocket *s) {
    close(s->socket_fd);
    WSACleanup();
}
