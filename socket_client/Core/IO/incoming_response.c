#include "incoming_response.h"

void init(struct IncomingResponse *response, void *data, int data_size) {
    response->data_size = data_size - 2;

    response->data = malloc(data_size - 2);
    memcpy(response->data, data + 2, data_size - 2);
}

void init_ok(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_OK;

    init(response, data, data_size);
}

void init_not_found(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_NOT_FOUND;

    init(response, data, data_size);
}

void init_bad_request(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_BAD_REQUEST;

    init(response, data, data_size);
}

void init_invalid_action(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_INVALID_ACTION;

    init(response, data, data_size);
}

void init_server_error(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_SERVER_ERROR;

    init(response, data, data_size);
}

void init_invalid_syntax(struct IncomingResponse *response, void *data, int data_size) {
    response->status = RESPONSE_INVALID_SYNTAX;

    init(response, data, data_size);
}

