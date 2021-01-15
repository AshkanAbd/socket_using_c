#ifndef SOCKET_SERVER_CONTROLLERS_H
#define SOCKET_SERVER_CONTROLLERS_H

#include "../Core/IO/outgoing_response.h"
#include "../Core/IO/incoming_request.h"
#include "../Core/db/sqlite/migration.h"
#include "../models/models.h"
#include "../callbacks/callbacks.h"
#include <time.h>

OutgoingResponse *sign_in(char **, int, char **, int);

OutgoingResponse *sign_up(char **, int, char **, int);

OutgoingResponse *post_list(char **, int, char **, int);

OutgoingResponse *get_post(char **, int, char **, int);

OutgoingResponse *create_post(char **, int, char **, int);

OutgoingResponse *update_post(char **, int, char **, int);

OutgoingResponse *delete_post(char **, int, char **, int);

#endif //SOCKET_SERVER_CONTROLLERS_H
