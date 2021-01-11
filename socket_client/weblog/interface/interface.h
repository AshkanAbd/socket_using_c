#ifndef SOCKET_CLIENT_INTERFACE_H
#define SOCKET_CLIENT_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include "../apis/apis.h"
#include "../life_cycle.h"

int get_life_cycle_status();

void change_life_cycle_status(int next_status);

void print_error_repose(IncomingResponse *response);

void start_status();

void sign_in_status();

void sign_up_status();

void post_list_status();

void post_action_status();

void get_post_status();


#endif //SOCKET_CLIENT_INTERFACE_H
