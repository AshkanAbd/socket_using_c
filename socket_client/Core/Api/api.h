#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "../IO/incoming_response.h"
#include "../IO/outgoing_request.h"
#include "../Socket/client.h"

struct IncomingResponse *read_api(struct Client *client, char *route, void *param, int param_size);

struct IncomingResponse *create_api(struct Client *client, char *route, void *param, int param_size,
                                    void *body, int body_size);

struct IncomingResponse *update_api(struct Client *client, char *route, void *param, int param_size,
                                    void *body, int body_size);

struct IncomingResponse *delete_api(struct Client *client, char *route, void *param, int param_size);

#endif //SOCKET_CLIENT_API_H
