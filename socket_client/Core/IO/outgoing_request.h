#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#include <string.h>
#include <stdlib.h>

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

struct OutgoingRequest {
    int action;
    char *route;
    void *body;
    int body_size;
    void *param;
    int param_size;
};

void init_read(struct OutgoingRequest *request, char *route, void *param, int param_size);

void init_create(struct OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size);

void init_update(struct OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size);

void init_delete(struct OutgoingRequest *request, char *route, void *param, int param_size);

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
