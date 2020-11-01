#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "../IO/incoming_response.h"
#include "../IO/outgoing_request.h"

struct IncomingResponse *read(char *route, void *param, int param_size);

struct IncomingResponse *create(char *route, void *param, int param_size, void *body, int body_size);

struct IncomingResponse *update(char *route, void *param, int param_size, void *body, int body_size);

struct IncomingResponse *delete(char *route, void *param, int param_size);

#endif //SOCKET_CLIENT_API_H
