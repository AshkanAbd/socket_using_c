#ifndef SOCKET_SERVER_OUTGOING_RESPONSE_H
#define SOCKET_SERVER_OUTGOING_RESPONSE_H

#include "../Socket/client.h"

#define RESPONSE_OK 1
#define RESPONSE_NOT_FOUND 2
#define RESPONSE_BAD_REQUEST 3
#define RESPONSE_INVALID_ACTION 4
#define RESPONSE_SERVER_ERROR 5
#define RESPONSE_INVALID_SYNTAX 6

static int MAX = 1024;

typedef struct OutgoingResponse OutgoingResponse;

struct OutgoingResponse {
    int status;
    void *data;
    int data_size;
};

void change_max(int max);

void init_ok(OutgoingResponse *response, void *data, int data_size);

void init_not_found(OutgoingResponse *response, void *data, int data_size);

void init_bad_request(OutgoingResponse *response, void *data, int data_size);

void init_invalid_action(OutgoingResponse *response, void *data, int data_size);

void init_server_error(OutgoingResponse *response, void *data, int data_size);

void init_invalid_syntax(OutgoingResponse *response, void *data, int data_size);

void send_to_client(OutgoingResponse *response, Client *client, int final_packet);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
