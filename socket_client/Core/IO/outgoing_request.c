#include "outgoing_request.h"

void init_request(struct OutgoingRequest *request, char *route, void *param, int param_size,
                  void *body, int body_size) {
    request->route = malloc(strlen(route));
    memcpy(request->route, route, strlen(route));

    if (param_size != 0) {
        request->param = malloc(param_size);
        memcpy(request->param, param, param_size);
    }

    if (body_size != 0) {
        request->body = malloc(body_size);
        memcpy(request->body, body, body_size);
    }
}

void init_read(struct OutgoingRequest *request, char *route, void *param, int param_size) {
    request->action = REQUEST_READ;

    init_request(request, route, param, param_size, NULL, 0);
}

void init_create(struct OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size) {
    request->action = REQUEST_CREATE;

    init_request(request, route, param, param_size, body, body_size);
}

void init_update(struct OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size) {
    request->action = REQUEST_UPDATE;

    init_request(request, route, param, param_size, body, body_size);
}

void init_delete(struct OutgoingRequest *request, char *route, void *param, int param_size) {
    request->action = REQUEST_DELETE;

    init_request(request, route, param, param_size, NULL, 0);
}
