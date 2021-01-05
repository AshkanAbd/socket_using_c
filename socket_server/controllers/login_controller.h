#ifndef SOCKET_SERVER_LOGIN_CONTROLLER_H
#define SOCKET_SERVER_LOGIN_CONTROLLER_H

#include "../Core/IO/outgoing_response.h"
#include "../Core/IO/incoming_request.h"
#include "../Core/db/sqlite/migration.h"
#include "../models/user.h"
#include "../models/token.h"
#include <time.h>

OutgoingResponse *sign_in(IncomingRequest *request);

OutgoingResponse *sign_up(IncomingRequest *request);

#endif //SOCKET_SERVER_LOGIN_CONTROLLER_H
