#ifndef SOCKET_SERVER_POST_CONTROLLER_H
#define SOCKET_SERVER_POST_CONTROLLER_H

#include "../Core/IO/outgoing_response.h"
#include "../Core/IO/incoming_request.h"
#include "../Core/db/sqlite/migration.h"
#include "../models/models.h"

OutgoingResponse *post_list(IncomingRequest *request);

#endif //SOCKET_SERVER_POST_CONTROLLER_H
