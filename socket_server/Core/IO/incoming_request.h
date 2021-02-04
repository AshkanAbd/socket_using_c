/**
 * The file that defines IncomingRequest struct.
 */
#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#include "../Socket/client.h"

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

typedef struct IncomingRequest IncomingRequest;

/**
 * The struct that holds parsed request from client.
 */
struct IncomingRequest {
    int action;
    char *route;
    void *param;
    int param_size;
    void *body;
    int body_size;
};

/**
 * Initializes IncomingRequest struct.
 * @param request
 * @param action
 * @param route
 * @param param
 * @param param_size
 * @param body
 * @param body_size
 */
void init_request(IncomingRequest *request, int action, char *route, void *param, int param_size,
                  void *body, int body_size);

/**
 * Parses the packet that receive from client into IncomingRequest struct.
 * @param request
 * @param buffer
 * @param buffer_size
 * @return
 */
int parse_request(IncomingRequest *request, const char *buffer, int buffer_size);

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
