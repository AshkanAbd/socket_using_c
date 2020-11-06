#ifndef SOCKET_CLIENT_INTERFACE_H
#define SOCKET_CLIENT_INTERFACE_H

#include "../Core/Api/api.h"

struct IncomingResponse *build_request();

void handle_response(struct IncomingResponse *response);

#endif //SOCKET_CLIENT_INTERFACE_H
