#include "outgoing_request.h"

void init_request(OutgoingRequest *request, char *route, void *param, int param_size,
                  void *body, int body_size) {
    request->route = malloc(strlen(route) + 1);
    memset(request->route, 0, strlen(route) + 1);
    memcpy(request->route, route, strlen(route));

    if (param_size != 0) {
        request->param = malloc(param_size);
        memset(request->param, 0, param_size);
        memcpy(request->param, param, param_size);

        request->param_size = param_size;
    } else {
        request->param = NULL;
        request->param_size = 0;
    }

    if (body_size != 0) {
        request->body = malloc(body_size);
        memset(request->body, 0, body_size);
        memcpy(request->body, body, body_size);

        request->body_size = body_size;
    } else {
        request->body = NULL;
        request->body_size = 0;
    }
}

void init_read(OutgoingRequest *request, char *route, void *param, int param_size) {
    request->action = REQUEST_READ;

    init_request(request, route, param, param_size, NULL, 0);
}

void init_create(OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size) {
    request->action = REQUEST_CREATE;

    init_request(request, route, param, param_size, body, body_size);
}

void init_update(OutgoingRequest *request, char *route, void *param, int param_size, void *body, int body_size) {
    request->action = REQUEST_UPDATE;

    init_request(request, route, param, param_size, body, body_size);
}

void init_delete(OutgoingRequest *request, char *route, void *param, int param_size) {
    request->action = REQUEST_DELETE;

    init_request(request, route, param, param_size, NULL, 0);
}
