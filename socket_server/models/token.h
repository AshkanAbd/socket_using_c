#ifndef SOCKET_SERVER_TOKEN_H
#define SOCKET_SERVER_TOKEN_H

#include "string.h"
#include "stdlib.h"

typedef struct Token Token;

struct Token {
    int id;
    char *token;
    int user_id;
};

void init_token(Token *token, int id, const char *login_token, int user_id);

void set_token_column(char **column, const char *value);

#endif //SOCKET_SERVER_TOKEN_H
