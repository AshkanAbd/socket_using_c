#ifndef SOCKET_SERVER_MODELS_H
#define SOCKET_SERVER_MODELS_H

#include "post.h"
#include "token.h"
#include "user.h"

int search_query(const char *table, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_MODELS_H
