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

char *response_to_str(struct IncomingResponse *response) {
    char *action_str = "";
    switch (response->status) {
        case RESPONSE_OK:
            action_str = "OK: ";
            break;
        case RESPONSE_NOT_FOUND:
            action_str = "NotFound: ";
            break;
        case RESPONSE_BAD_REQUEST:
            action_str = "BadRequest: ";
            break;
        case RESPONSE_INVALID_ACTION:
            action_str = "InvalidAction: ";
            break;
        case RESPONSE_SERVER_ERROR:
            action_str = "ServerError: ";
            break;
        case RESPONSE_INVALID_SYNTAX:
            action_str = "InvalidSyntax: ";
            break;
    }

    char *data_str = malloc(response->data_size);
    memset(data_str, 0, response->data_size);
    memcpy(data_str, response->data, response->data_size);
    if (strlen(data_str) == 0) {
        data_str = "<content empty>";
    }

    char *response_str = malloc(strlen(action_str) + strlen(data_str) + 1);
    memset(response_str, 0, strlen(action_str) + strlen(data_str) + 1);
    memcpy(response_str, action_str, strlen(action_str));
    memcpy(response_str + strlen(action_str), data_str, strlen(data_str));

    return response_str;
}
