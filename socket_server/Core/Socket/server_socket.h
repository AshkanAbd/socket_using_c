/**
 * The file that defines ServerSocket struct.
 */
#ifndef SOCKET_SERVER_SERVER_SOCKET_H
#define SOCKET_SERVER_SERVER_SOCKET_H

#include <errno.h>
#include <winsock2.h>
#include <io.h>

typedef struct ServerSocket ServerSocket;

/**
 * The struct that holds server's socket data.
 */
struct ServerSocket {
    int socket_fd;
    struct sockaddr_in server_address;
};

/**
 * Creates the socket.
 * @param s
 * @return
 */
int create_socket(ServerSocket *s);

/**
 * Assigns port to the socket.
 * @param s
 * @param port
 */
void assign_port(ServerSocket *s, int port);

/**
 * Binds the socket into the address.
 * @param s
 * @return
 */
int bind_socket(ServerSocket *s);

/**
 * Starts to listen from the socket.
 * @param s
 * @return
 */
int listen_socket(ServerSocket *s);

/**
 * Accepts connection from the socket.
 * @param s
 * @return
 */
int accept_connection(ServerSocket *s);

/**
 * Cloeses the socket.
 * @param s
 */
void close_socket(ServerSocket *s);

#endif //SOCKET_SERVER_SERVER_SOCKET_H
