#include "user.h"

void init_user_full(User *user, int id, const char *username, const char *password,
                    const char *created_at, const char *updated_at) {
    user->id = id;

    set_user_column(&user->username, username);

    set_user_column(&user->password, password);

    set_user_column(&user->created_at, created_at);

    set_user_column(&user->updated_at, updated_at);
}

void init_user(User *user, const char *username, const char *password) {
    set_user_column(&user->username, username);

    set_user_column(&user->password, password);
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

int user_search_by_username(const char *username, void *ptr, int (*callback)(void *, int, char **, char **),
                            char **msg) {
    char *base_search_sql = "SELECT * FROM users WHERE username = ";
    size_t custom_search_sql_size = strlen(base_search_sql) + 1 + strlen(username) + 2;
    char *custom_search_sql = malloc(custom_search_sql_size);
    memset(custom_search_sql, 0, custom_search_sql_size);

    memcpy(custom_search_sql, base_search_sql, strlen(base_search_sql));

    *(custom_search_sql + strlen(base_search_sql)) = '\'';
    memcpy(custom_search_sql + strlen(base_search_sql) + 1, username, strlen(username));
    *(custom_search_sql + strlen(base_search_sql) + 1 + strlen(username)) = '\'';

    return sqlite3_exec(db_connection, custom_search_sql, callback, ptr, msg);
}

int insert_user(User *user, int (*callback)(void *, int, char **, char **), char **msg) {
    if (user->username == NULL) {
        *msg = "username is null";
        return 0;
    }
    if (user->password == NULL) {
        *msg = "password is null";
        return 0;
    }
    char *base_insert_sql = "INSERT INTO users (username, password) VALUES (";
    size_t custom_insert_sql_size = strlen(base_insert_sql) + 1 + strlen(user->username) +
                                    3 + strlen(user->password) + 3;
    char *custom_insert_sql = malloc(custom_insert_sql_size);
    memset(custom_insert_sql, 0, custom_insert_sql_size);
    memcpy(custom_insert_sql, base_insert_sql, strlen(base_insert_sql));

    *(custom_insert_sql + strlen(base_insert_sql)) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1, user->username, strlen(user->username));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username)) = '\'';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username) + 1) = ',';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username) + 2) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username) + 3,
           user->password, strlen(user->password));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username) + 3 + strlen(user->password)) = '\'';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(user->username) + 3 + strlen(user->password) + 1) = ')';

    return sqlite3_exec(db_connection, custom_insert_sql, callback, 0, msg);
}

int user_search_by_id(const char *id, void *ptr, int (*callback)(void *, int, char **, char **), char **msg) {
    char *base_search_sql = "SELECT * FROM users WHERE id = ";
    size_t custom_search_sql_size = strlen(base_search_sql) + 1 + strlen(id) + 2;
    char *custom_search_sql = malloc(custom_search_sql_size);
    memset(custom_search_sql, 0, custom_search_sql_size);

    memcpy(custom_search_sql, base_search_sql, strlen(base_search_sql));

    *(custom_search_sql + strlen(base_search_sql)) = '\'';
    memcpy(custom_search_sql + strlen(base_search_sql) + 1, id, strlen(id));
    *(custom_search_sql + strlen(base_search_sql) + 1 + strlen(id)) = '\'';

    return sqlite3_exec(db_connection, custom_search_sql, callback, ptr, msg);
}