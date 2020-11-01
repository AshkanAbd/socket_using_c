#include "api.h"

void prepare_request(struct OutgoingRequest *request, char *buffer) {
    memcpy(buffer, (char *) &request->action, 1);

    memcpy(buffer + 1, request->route, strlen(request->route));

    if (request->param_size != 0 && request->body_size != 0) {

        memcpy(buffer + 1 + strlen(request->route) + 1, request->param, request->param_size);

        memcpy(buffer + 1 + strlen(request->route) + 1 + request->param_size + 1,
               request->body, request->body_size);

    } else if (request->param_size != 0 && request->body_size == 0) {

        memcpy(buffer + 1 + strlen(request->route) + 1, request->param, request->param_size);

    } else if (request->param_size == 0 && request->body_size != 0) {

        memcpy(buffer + 1 + strlen(request->route) + 1 + 1, request->body, request->body_size);

    }
}

struct IncomingResponse *read_api(struct Client *client, char *route, void *param, int param_size) {
    struct OutgoingRequest request;
    init_read(&request, route, param, param_size);

    int request_buffer_size = 1 + 1 + (int) strlen(request.route) + 1 + request.param_size + 1 + request.body_size + 1;
    char *request_buffer = malloc(request_buffer_size);
    memset(request_buffer, 0x1D, request_buffer_size);

    prepare_request(&request, request_buffer);

    send(client->socket, request_buffer, request_buffer_size, 0);

    int response_buffer_size = client->buffer_size;
    char *response_buffer = malloc(response_buffer_size);
    memset(response_buffer, 0x1D, response_buffer_size);

    recv(client->socket, response_buffer, response_buffer_size, 0);
}

struct IncomingResponse *create_api(struct Client *client, char *route, void *param, int param_size,
                                    void *body, int body_size) {
    struct OutgoingRequest request;
    init_create(&request, route, param, param_size, body, body_size);

    int request_buffer_size = 1 + 1 + (int) strlen(request.route) + 1 + request.param_size + 1 + request.body_size + 1;
    char *request_buffer = malloc(request_buffer_size);
    memset(request_buffer, 0x1D, request_buffer_size);

    prepare_request(&request, request_buffer);

    send(client->socket, request_buffer, request_buffer_size, 0);

    int response_buffer_size = client->buffer_size;
    char *response_buffer = malloc(response_buffer_size);
    memset(response_buffer, 0x1D, response_buffer_size);

    recv(client->socket, response_buffer, response_buffer_size, 0);
}

struct IncomingResponse *update_api(struct Client *client, char *route, void *param, int param_size,
                                    void *body, int body_size) {
    struct OutgoingRequest request;
    init_update(&request, route, param, param_size, body, body_size);

    int request_buffer_size = 1 + 1 + (int) strlen(request.route) + 1 + request.param_size + 1 + request.body_size + 1;
    char *request_buffer = malloc(request_buffer_size);
    memset(request_buffer, 0x1D, request_buffer_size);

    prepare_request(&request, request_buffer);

    send(client->socket, request_buffer, request_buffer_size, 0);

    int response_buffer_size = client->buffer_size;
    char *response_buffer = malloc(response_buffer_size);
    memset(response_buffer, 0x1D, response_buffer_size);

    recv(client->socket, response_buffer, response_buffer_size, 0);
}

struct IncomingResponse *delete_api(struct Client *client, char *route, void *param, int param_size) {
    struct OutgoingRequest request;
    init_delete(&request, route, param, param_size);

    int request_buffer_size = 1 + 1 + (int) strlen(request.route) + 1 + request.param_size + 1 + request.body_size + 1;
    char *request_buffer = malloc(request_buffer_size);
    memset(request_buffer, 0x1D, request_buffer_size);

    prepare_request(&request, request_buffer);

    send(client->socket, request_buffer, request_buffer_size, 0);

    int response_buffer_size = client->buffer_size;
    char *response_buffer = malloc(response_buffer_size);
    memset(response_buffer, 0x1D, response_buffer_size);

    recv(client->socket, response_buffer, response_buffer_size, 0);
}
