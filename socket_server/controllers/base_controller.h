#ifndef SOCKET_SERVER_BASE_CONTROLLER_H
#define SOCKET_SERVER_BASE_CONTROLLER_H

#include "../Core/IO/outgoing_response.h"
#include "../Core/IO/incoming_request.h"

struct OutgoingResponse *sample(struct IncomingRequest *request);

#endif //SOCKET_SERVER_BASE_CONTROLLER_H
