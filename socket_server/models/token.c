#include "token.h"

void init_token_full(Token *token, int id, const char *login_token, int user_id, char *created_at, char *updated_at) {
    token->id = id;
    token->user_id = user_id;

    set_token_column(&token->token, login_token);

    set_token_column(&token->created_at, created_at);

    set_token_column(&token->updated_at, updated_at);
}

void init_token(Token *token, const char *login_token, int user_id) {
    token->user_id = user_id;

    set_token_column(&token->token, login_token);
}

void set_token_column(char **column, const char *value) {
    if (column == NULL) {
        return;
    }

    if (*column != NULL) {
        free(*column);
    }

    if (value != NULL) {
        *column = malloc(strlen(value) + 1);
        memset(*column, 0, strlen(value) + 1);
        memcpy(*column, value, strlen(value));
    } else {
        *column = NULL;
    }
}

int insert_token(Token *token, int (*callback)(void *, int, char **, char **), char **msg) {
    if (token->token == NULL) {
        *msg = "token is null";
        return 0;
    }

    if (token->user_id == 0) {
        *msg = "token is invalid";
        return 0;
    }

    char *base_insert_sql = "INSERT INTO tokens (token, user_id) VALUES (";
    size_t custom_insert_sql_size = strlen(base_insert_sql) + 1 + strlen(token->token) + 5;
    char *custom_insert_sql = malloc(custom_insert_sql_size);
    memset(custom_insert_sql, 0, custom_insert_sql_size);

    memcpy(custom_insert_sql, base_insert_sql, strlen(base_insert_sql));

    *(custom_insert_sql + strlen(base_insert_sql)) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1, token->token, strlen(token->token));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(token->token)) = '\'';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(token->token) + 1) = ',';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(token->token) + 2) = (char) ('0' + token->user_id);
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(token->token) + 3) = ')';

    return sqlite3_exec(db_connection, custom_insert_sql, callback, 0, msg);
}
