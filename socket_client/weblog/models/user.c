#include "user.h"

void init_user(User *user) {
    user->id = 0;

    set_user_column(&user->username, "", 0);

    set_user_column(&user->password, "", 0);

    set_user_column(&user->token, "", 0);
}

void set_user_column(char **column, const char *value, int with_free) {
    if (column == NULL) {
        return;
    }

    if (*column != NULL && with_free) {
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
