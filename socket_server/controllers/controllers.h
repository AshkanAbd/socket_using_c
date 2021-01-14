#ifndef SOCKET_SERVER_CONTROLLERS_H
#define SOCKET_SERVER_CONTROLLERS_H

#include "../Core/IO/outgoing_response.h"
#include "../Core/IO/incoming_request.h"
#include "../Core/db/sqlite/migration.h"
#include "../models/models.h"
#include "../callbacks/callbacks.h"
#include <time.h>

OutgoingResponse *sign_in(IncomingRequest *request);

OutgoingResponse *sign_up(IncomingRequest *request);

OutgoingResponse *post_list(IncomingRequest *request);

OutgoingResponse *get_post(IncomingRequest *request);

OutgoingResponse *create_post(IncomingRequest *request);

#endif //SOCKET_SERVER_CONTROLLERS_H
