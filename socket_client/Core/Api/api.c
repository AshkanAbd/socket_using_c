#include "api.h"

struct Client *request_client() {
    struct ClientSocket *client_socket = malloc(sizeof(struct ClientSocket));
    memset(client_socket, 0, sizeof(struct ClientSocket));

    struct Client *client = malloc(sizeof(struct Client));
    memset(client, 0, sizeof(struct Client));

    init_socket(client_socket);

    init_client(client, MAX, client_socket->socket_fd);
}

void prepare_request(struct OutgoingRequest *request, char *buffer) {
    memcpy(buffer, (char *) &request->action, 1);

    memcpy(buffer + 2, request->route, strlen(request->route));

    if (request->param_size != 0 && request->body_size != 0) {

        memcpy(buffer + 2 + strlen(request->route) + 1, request->param, request->param_size);

        memcpy(buffer + 2 + strlen(request->route) + 1 + request->param_size + 1,
               request->body, request->body_size);

    } else if (request->param_size != 0 && request->body_size == 0) {

        memcpy(buffer + 2 + strlen(request->route) + 1, request->param, request->param_size);

    } else if (request->param_size == 0 && request->body_size != 0) {

        memcpy(buffer + 2 + strlen(request->route) + 1 + 1, request->body, request->body_size);

    }
}

int has_more_packets(char *buffer, int buffer_size) {
    register int i;
    for (i = 0; i < buffer_size; ++i) {
        if (*(buffer + i) == 0x1C) {
            *(buffer + i) = 0;
            return 0;
        }
    }
    return 1;
}

struct IncomingResponse *send_request(struct OutgoingRequest *request, struct Client *client) {
    int request_buffer_size = 1 + 1 + (int) strlen(request->route) + 1 + request->param_size +
                              1 + request->body_size + 1;
    char *request_buffer = malloc(request_buffer_size + 1);
    memset(request_buffer, 0x1D, request_buffer_size);
    *(request_buffer + request_buffer_size) = 0;

    prepare_request(request, request_buffer);

    send(client->socket, request_buffer, request_buffer_size, 0);

    int response_buffer_size = client->buffer_size;
    int current_buffer_size = client->buffer_size;
    int response_buffer_index = 0;
    char *response_buffer = malloc(response_buffer_size + 1);
    memset(response_buffer, 0, response_buffer_size);

    recv(client->socket, response_buffer, current_buffer_size, 0);

    int count = 1;
    while (has_more_packets(response_buffer + response_buffer_index, current_buffer_size)) {
        count++;

        char *tmp = malloc(client->buffer_size);
        memset(tmp, 0, client->buffer_size);
        recv(client->socket, tmp, client->buffer_size, 0);
        int wrong_packet_count = 0;
        register int i;
        for (i = 0; i < client->buffer_size; ++i) {
            if (*(tmp + i) == 0) {
                wrong_packet_count++;
            }
        }

        response_buffer_index = response_buffer_size;
        current_buffer_size = client->buffer_size - wrong_packet_count;
        response_buffer_size += current_buffer_size;

        response_buffer = realloc(response_buffer, response_buffer_size);
        memset(response_buffer + response_buffer_index, 0, current_buffer_size);
        memcpy(response_buffer + response_buffer_index, tmp, current_buffer_size);
    }
    printf("%d\n", count);

    struct IncomingResponse *response = malloc(sizeof(struct IncomingResponse));
    memset(response, 0, sizeof(struct IncomingResponse));
    if (*response_buffer == RESPONSE_OK) {
        init_ok(response, response_buffer, response_buffer_size);
    } else if (*response_buffer == RESPONSE_NOT_FOUND) {
        init_not_found(response, response_buffer, response_buffer_size);
    } else if (*response_buffer == RESPONSE_BAD_REQUEST) {
        init_bad_request(response, response_buffer, response_buffer_size);
    } else if (*response_buffer == RESPONSE_INVALID_ACTION) {
        init_invalid_action(response, response_buffer, response_buffer_size);
    } else if (*response_buffer == RESPONSE_SERVER_ERROR) {
        init_server_error(response, response_buffer, response_buffer_size);
    } else if (*response_buffer == RESPONSE_INVALID_SYNTAX) {
        init_invalid_syntax(response, response_buffer, response_buffer_size);
    }
    return response;
}

struct IncomingResponse *api_read(char *route, void *param, int param_size) {
    struct Client *client = request_client();

    struct OutgoingRequest *request = malloc(sizeof(struct OutgoingRequest));
    memset(request, 0, sizeof(struct OutgoingRequest));

    init_read(request, route, param, param_size);

    struct IncomingResponse *response = send_request(request, client);
    return response;
}

struct IncomingResponse *api_create(char *route, void *param, int param_size, void *body, int body_size) {
    struct Client *client = request_client();

    struct OutgoingRequest *request = malloc(sizeof(struct OutgoingRequest));
    memset(request, 0, sizeof(struct OutgoingRequest));

    init_create(request, route, param, param_size, body, body_size);

    struct IncomingResponse *response = send_request(request, client);
    return response;
}

struct IncomingResponse *api_update(char *route, void *param, int param_size, void *body, int body_size) {
    struct Client *client = request_client();

    struct OutgoingRequest *request = malloc(sizeof(struct OutgoingRequest));
    memset(request, 0, sizeof(struct OutgoingRequest));

    init_update(request, route, param, param_size, body, body_size);

    struct IncomingResponse *response = send_request(request, client);
    return response;
}

struct IncomingResponse *api_delete(char *route, void *param, int param_size) {
    struct Client *client = request_client();

    struct OutgoingRequest *request = malloc(sizeof(struct OutgoingRequest));
    memset(request, 0, sizeof(struct OutgoingRequest));

    init_delete(request, route, param, param_size);

    struct IncomingResponse *response = send_request(request, client);
    return response;
}
