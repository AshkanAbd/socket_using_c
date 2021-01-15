#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "../IO/incoming_response.h"
#include "../IO/outgoing_request.h"
#include "../Socket/client.h"
#include "../Socket/client_socket.h"

struct IncomingResponse *send_request(OutgoingRequest *request, Client *client);

struct IncomingResponse *api_read(char *route, void *param, int param_size, char *ip, int port);

struct IncomingResponse *
api_create(char *route, void *param, int param_size, void *body, int body_size, char *ip, int port);

struct IncomingResponse *
api_update(char *route, void *param, int param_size, void *body, int body_size, char *ip, int port);

struct IncomingResponse *api_delete(char *route, void *param, int param_size, char *ip, int port);

#endif //SOCKET_CLIENT_API_H
