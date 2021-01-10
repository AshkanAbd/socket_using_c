#ifndef SOCKET_SERVER_TOKEN_H
#define SOCKET_SERVER_TOKEN_H

#include "string.h"
#include "stdlib.h"
#include "../Core/db/sqlite/migration.h"

typedef struct Token Token;

struct Token {
    int id;
    char *token;
    int user_id;
    char *created_at;
    char *updated_at;
};

void init_token_full(Token *token, int id, const char *login_token, int user_id, char *created_at, char *updated_at);

void init_token(Token *token, const char *login_token, int user_id);

void set_token_column(char **column, const char *value);

int insert_token(Token *token, int (*callback)(void *, int, char **, char **), char **msg);

int find_token(const char *token, void *ptr, int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_TOKEN_H
