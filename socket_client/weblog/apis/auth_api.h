#ifndef SOCKET_CLIENT_AUTH_API_H
#define SOCKET_CLIENT_AUTH_API_H

#include "../../Core/Api/api.h"

void sign_in_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

void sign_up_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

#endif //SOCKET_CLIENT_AUTH_API_H
