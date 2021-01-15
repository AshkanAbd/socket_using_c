#ifndef SOCKET_CLIENT_APIS_H
#define SOCKET_CLIENT_APIS_H

#include "../../Core/Api/api.h"

void sign_in_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

void sign_up_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr);

void post_list_api(void callback(IncomingResponse *, void *), void *ptr);

void get_post_api(const char *id, void callback(IncomingResponse *, void *), void *ptr);

void create_post_api(const char *token, const char *post_char, void callback(IncomingResponse *, void *), void *ptr);

void update_post_api(const char *id, const char *token, const char *post_char,
                     void callback(IncomingResponse *, void *), void *ptr);

void delete_post_api(const char *id, const char *token, void callback(IncomingResponse *, void *), void *ptr);

#endif //SOCKET_CLIENT_APIS_H
