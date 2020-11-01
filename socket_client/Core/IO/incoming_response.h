#ifndef SOCKET_SERVER_OUTGOING_RESPONSE_H
#define SOCKET_SERVER_OUTGOING_RESPONSE_H

#include <string.h>
#include <stdlib.h>

#define RESPONSE_OK 1
#define RESPONSE_NOT_FOUND 2
#define RESPONSE_BAD_REQUEST 3
#define RESPONSE_INVALID_ACTION 4
#define RESPONSE_SERVER_ERROR 5

struct IncomingResponse {
    int status;
    void *data;
    int data_size;
};

void init(struct IncomingResponse *response, void *data, int data_size);

void init_ok(struct IncomingResponse *response, void *data, int data_size);

void init_not_found(struct IncomingResponse *response, void *data, int data_size);

void init_bad_request(struct IncomingResponse *response, void *data, int data_size);

void init_invalid_action(struct IncomingResponse *response, void *data, int data_size);

void init_server_error(struct IncomingResponse *response, void *data, int data_size);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
