#ifndef SOCKET_CLIENT_INTERFACE_H
#define SOCKET_CLIENT_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include "../apis/apis.h"
#include "../life_cycle.h"

void start_status(int *current_status);

void sign_in_status(int *current_status);

void sign_up_status(int *current_status);

#endif //SOCKET_CLIENT_INTERFACE_H
