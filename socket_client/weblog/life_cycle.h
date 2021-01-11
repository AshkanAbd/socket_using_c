#ifndef SOCKET_CLIENT_LIFE_CYCLE_H
#define SOCKET_CLIENT_LIFE_CYCLE_H

#include "models/models.h"
#include "interface/interface.h"

#define STATUS_START            0
#define STATUS_SIGN_IN          1
#define STATUS_SIGN_UP          2
#define STATUS_POST_LIST    3
#define STATUS_GET_ONE_POST     4
#define STATUS_CREATE_POST      5
#define STATUS_UPDATE_POST      6
#define STATUS_DELETE_POST      7


void start_life_cycle(const char *ip, int port);

#endif //SOCKET_CLIENT_LIFE_CYCLE_H
