#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#include <string.h>
#include <stdlib.h>

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

struct IncomingRequest {
    int action;
    char *route;
    void *payload;
    int payload_size;
};

void init_request(struct IncomingRequest *request, int action, char *route, void *payload, int payload_size);

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
