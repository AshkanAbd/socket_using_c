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
