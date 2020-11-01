#ifndef SOCKET_SERVER_INCOMING_REQUEST_H
#define SOCKET_SERVER_INCOMING_REQUEST_H

#define REQUEST_READ 1
#define REQUEST_CREATE 2
#define REQUEST_UPDATE 3
#define REQUEST_DELETE 4

struct IncomingRequest {
    int action;
    char *route;
    void *payload;
};

#endif //SOCKET_SERVER_INCOMING_REQUEST_H
