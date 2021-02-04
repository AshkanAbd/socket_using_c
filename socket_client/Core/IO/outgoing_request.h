/**
 * The file that defines OutgoingRequest struct.
 */
#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#include <string.h>
#include <stdlib.h>

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

typedef struct OutgoingRequest OutgoingRequest;

/**
 * The struct that holds request information.
 */
struct OutgoingRequest {
    int action;
    char *route;
    void *body;
    int body_size;
    void *param;
    int param_size;
};

/**
 * Creates a GET request from given data.
 * @param request
 * @param route
 * @param param
 * @param param_size
 */
void init_read(OutgoingRequest *request, char *route, void *param, int param_size);

/**
 * Creates a POST request from given data.
 * @param request
 * @param route
 * @param param
 * @param param_size
 * @param body
 * @param body_size
 */
void init_create(OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size);

/**
 * Creates a PUT request from given data.
 * @param request
 * @param route
 * @param param
 * @param param_size
 * @param body
 * @param body_size
 */
void init_update(OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size);

/**
 * Creates a DELETE request from given data.
 * @param request
 * @param route
 * @param param
 * @param param_size
 */
void init_delete(OutgoingRequest *request, char *route, void *param, int param_size);

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
