#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#include "../Socket/client.h"

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

struct IncomingRequest {
    int action;
    char *route;
    void *param;
    int param_size;
    void *body;
    int body_size;
};

void init_request(struct IncomingRequest *request, int action, char *route, void *param, int param_size,
                  void *body, int body_size);

int parse_request(struct IncomingRequest *request, const char *buffer, int buffer_size);

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
