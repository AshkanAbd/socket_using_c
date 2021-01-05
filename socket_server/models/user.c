#include "user.h"

void init_user(User *user, int id, const char *username, const char *password,
               const char *created_at, const char *updated_at) {
    user->id = id;

    set_user_column(&user->username, username);

    set_user_column(&user->password, password);

    set_user_column(&user->created_at, created_at);

    set_user_column(&user->updated_at, updated_at);
}

void set_user_column(char **column, const char *value) {
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
