#ifndef SOCKET_CLIENT_APIS_H
#define SOCKET_CLIENT_APIS_H

#include "../../Core/Api/api.h"

void sign_in_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

void sign_up_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

void post_list_api(void callback(IncomingResponse *, void *), void *ptr);

void get_post_api(const char *id, void callback(IncomingResponse *, void *), void *ptr);

#endif //SOCKET_CLIENT_APIS_H
