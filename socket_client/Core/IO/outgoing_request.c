#include "outgoing_request.h"

void init_request(struct OutgoingRequest *request, char *route, void *payload, int payload_size) {
    request->route = malloc(strlen(route));
    memcpy(request->route, route, strlen(route));

    request->payload_size = payload_size;
    request->payload = malloc(payload_size);
    memcpy(request->payload, payload, payload_size);
}

void init_read(struct OutgoingRequest *request, char *route, void *payload, int payload_size) {
    request->action = REQUEST_READ;

    init_request(request, route, payload, payload_size);
}

void init_create(struct OutgoingRequest *request, char *route, void *payload, int payload_size) {
    request->action = REQUEST_CREATE;

    init_request(request, route, payload, payload_size);
}

void init_update(struct OutgoingRequest *request, char *route, void *payload, int payload_size) {
    request->action = REQUEST_UPDATE;

    init_request(request, route, payload, payload_size);
}

void init_delete(struct OutgoingRequest *request, char *route, void *payload, int payload_size) {
    request->action = REQUEST_DELETE;

    init_request(request, route, payload, payload_size);
}
