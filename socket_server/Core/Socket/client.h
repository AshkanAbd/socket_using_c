/**
 * The file that defines Client struct.
 */
#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <stdio.h>
#include <winsock2.h>
#include <pthread.h>

typedef struct Client Client;

/**
 * The struct that holds client's socket data.
 */
struct Client {
    int *socket;
};

/**
 * Initializes client struct from given data..
 * @param c
 * @param socket
 */
void init_client(Client *c, int *socket);

/**
 * Closes client socket.
 * @param c
 */
void close_client(Client *c);

#endif //SOCKET_SERVER_CLIENT_H