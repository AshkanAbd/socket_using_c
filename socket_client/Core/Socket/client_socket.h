/**
 * The file that defines ClientSocket struct.
 */
#ifndef SOCKET_CLIENT_CLIENT_SOCKET_H
#define SOCKET_CLIENT_CLIENT_SOCKET_H

#include <string.h>
#include <winsock2.h>
#include <stdio.h>
#include <io.h>

typedef struct ClientSocket ClientSocket;

/**
 * The struct that holds socket data.
 */
struct ClientSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

/**
 * Creates a TCP socket.
 * @param s
 * @return
 */
int create_socket(ClientSocket *s);

/**
 * Assigns IP and port to the socket.
 * @param s
 * @param ip
 * @param port
 */
void assign_port(ClientSocket *s, char *ip, int port);

/**
 * Connects the socket to server.
 * @param s
 * @return
 */
int connect_socket(ClientSocket *s);

/**
 * Closes the socket.
 * @param s
 */
void close_socket(ClientSocket *s);

/**
 * Creates a socket with given IP and port.
 * @param client_socket
 * @param ip
 * @param port
 */
void init_socket(ClientSocket *client_socket, char *ip, int port);

#endif //SOCKET_CLIENT_CLIENT_SOCKET_H
