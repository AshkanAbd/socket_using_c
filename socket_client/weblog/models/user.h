#ifndef SOCKET_CLIENT_USER_H
#define SOCKET_CLIENT_USER_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct User User;

struct User {
    int id;
    char *username;
    char *password;
    char *token;
};

void init_user(User *user);

void set_user_column(char **column, const char *value, int with_free);

#endif //SOCKET_CLIENT_USER_H
