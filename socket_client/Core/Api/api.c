#include "api.h"

struct IncomingResponse *read(char *route, void *param, int param_size) {
    struct OutgoingRequest request;
    init_read(&request, route, param, param_size);
}

struct IncomingResponse *create(char *route, void *param, int param_size, void *body, int body_size) {
    struct OutgoingRequest request;
    init_create(&request, route, param, param_size, body, body_size);
}

struct IncomingResponse *update(char *route, void *param, int param_size, void *body, int body_size) {
    struct OutgoingRequest request;
    init_update(&request, route, param, param_size, body, body_size);
}

struct IncomingResponse *delete(char *route, void *param, int param_size) {
    struct OutgoingRequest request;
    init_delete(&request, route, param, param_size);
}
