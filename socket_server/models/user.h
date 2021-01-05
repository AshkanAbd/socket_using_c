#ifndef SOCKET_SERVER_USER_H
#define SOCKET_SERVER_USER_H

#include "string.h"
#include "stdlib.h"

typedef struct User User;

struct User {
    int id;
    char *username;
    char *password;
    char *created_at;
    char *updated_at;
};

void init_user(User *user, int id, const char *username, const char *password,
               const char *created_at, const char *updated_at);

void set_user_column(char **column, const char *value);

#endif //SOCKET_SERVER_USER_H
