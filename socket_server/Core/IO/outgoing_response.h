#ifndef SOCKET_SERVER_OUTGOING_RESPONSE_H
#define SOCKET_SERVER_OUTGOING_RESPONSE_H

#include <string.h>
#include <stdlib.h>

#define RESPONSE_OK 1
#define RESPONSE_NOT_FOUND 2
#define RESPONSE_BAD_REQUEST 3
#define RESPONSE_INVALID_ACTION 4
#define RESPONSE_SERVER_ERROR 5
#define RESPONSE_INVALID_SYNTAX 6

struct OutgoingResponse {
    int status;
    void *data;
    int data_size;
};

void init_ok(struct OutgoingResponse *response, void *data, int data_size);

void init_not_found(struct OutgoingResponse *response, void *data, int data_size);

void init_bad_request(struct OutgoingResponse *response, void *data, int data_size);

void init_invalid_action(struct OutgoingResponse *response, void *data, int data_size);

void init_server_error(struct OutgoingResponse *response, void *data, int data_size);

void init_invalid_syntax(struct OutgoingResponse *response, void *data, int data_size);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
