/**
 * The file that defines Client struct.
 */
#ifndef SOCKET_SERVER_CLIENT_H
#define SOCKET_SERVER_CLIENT_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <winsock2.h>
#include <pthread.h>

static int MAX = 1024;

typedef struct Client Client;

/**
 * The struct that holds client packet data.
 */
struct Client {
    int socket, buffer_size;
};

/**
 * Sets packets max size.
 * @param max
 */
void change_max(int max);

/**
 * Initializes a client struct.
 * @param c
 * @param buffer_size
 * @param socket
 */
void init_client(Client *c, int buffer_size, int socket);

#endif //SOCKET_SERVER_CLIENT_H
