#ifndef SOCKET_SERVER_USER_H
#define SOCKET_SERVER_USER_H

#include "string.h"
#include "stdlib.h"
#include "../Core/db/sqlite/migration.h"

typedef struct User User;

struct User {
    int id;
    char *username;
    char *password;
    char *created_at;
    char *updated_at;
};

void init_user_full(User *user, int id, const char *username, const char *password,
                    const char *created_at, const char *updated_at);

void init_user(User *user, const char *username, const char *password);

void set_user_column(char **column, const char *value);

//int user_search_by_username(const char *username, void *ptr, int (*callback)(void *, int, char **, char **),
//                            char **msg);

//int user_search_by_id(const char *id, void *ptr, int (*callback)(void *, int, char **, char **), char **msg);

int insert_user(User *user, int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_USER_H
