#ifndef SOCKET_SERVER_MODELS_H
#define SOCKET_SERVER_MODELS_H

#include "post.h"
#include "token.h"
#include "user.h"

#define POST_TYPE   1
#define TOKEN_TYPE  2
#define USER_TYPE   3

int search_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

int insert_query(int type, const void *obj, void *ptr, int (*callback)(void *, int, char **, char **), char **msg);

int update_query(int type, const char *column, const char *value, const void *obj, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

int delete_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_MODELS_H
