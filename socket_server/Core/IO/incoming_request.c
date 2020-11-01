#include "incoming_request.h"

void init_request(struct IncomingRequest *request, int action, char *route, void *param, int param_size,
                  void *body, int body_size) {
    request->action = action;

    request->route = malloc(strlen(route));
    memcpy(request->route, route, strlen(route));

    request->param_size = param_size;
    request->param = malloc(param_size);
    memcpy(request->param, param, param_size);

    request->body_size = body_size;
    request->body = malloc(body_size);
    memcpy(request->body, body, body_size);
}
