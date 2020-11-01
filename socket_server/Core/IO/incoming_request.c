#include "incoming_request.h"

void init_request(struct IncomingRequest *request, int action, char *route, void *payload, int payload_size) {
    request->action = action;

    request->route = malloc(strlen(route));
    memcpy(request->route, route, strlen(route));

    request->payload_size = payload_size;
    request->payload = malloc(payload_size);
    memcpy(request->payload, payload, payload_size);
}
