#include "models.h"

const char *get_table(int type, char **msg) {
    char *table = NULL;
    if (type == POST_TYPE) {
        table = "posts";
    } else if (type == TOKEN_TYPE) {
        table = "tokens";
    } else if (type == USER_TYPE) {
        table = "users";
    } else {
        *msg = "Invalid insert type.";
    }
    return table;
}

const char *get_columns(int type, char **msg) {
    char *columns = NULL;
    if (type == POST_TYPE) {
        columns = "title, description, user_id";
    } else if (type == TOKEN_TYPE) {
        columns = "token, user_id";
    } else if (type == USER_TYPE) {
        columns = "username, password";
    } else {
        *msg = "Invalid insert type.";
    }
    return columns;
}

const char *get_value_template(int type, char **msg) {
    char *values_template = NULL;
    if (type == POST_TYPE) {
        values_template = "'%s', '%s', '%d'";
    } else if (type == TOKEN_TYPE) {
        values_template = "'%s', '%d'";
    } else if (type == USER_TYPE) {
        values_template = "'%s', '%s'";
    } else {
        *msg = "Invalid insert type.";
    }
    return values_template;
}


int search_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg) {
    const char *buffer_template = "SELECT * FROM %s WHERE %s = '%s'";

    const char *table = get_table(type, msg);
    if (table == NULL) {
        return 1;
    }

    size_t buffer_size = strlen(buffer_template) - (2 * 3) + strlen(table) + strlen(column) + strlen(value) + 1;

    char *buffer = malloc(buffer_size);
    memset(buffer, 0, buffer_size);

    sprintf(buffer, buffer_template, table, column, value);

    return sqlite3_exec(db_connection, buffer, callback, ptr, msg);
}

int insert_query(int type, const void *obj, void *ptr, int (*callback)(void *, int, char **, char **), char **msg) {
    const char *table = get_table(type, msg);
    if (table == NULL) {
        return 1;
    }

    const char *columns = get_columns(type, msg);
    if (columns == NULL) {
        return 1;
    }

    const char *values_template = get_value_template(type, msg);
    if (values_template == NULL) {
        return 1;
    }

    char *values = 0;
    size_t values_size = 0;

    if (type == POST_TYPE) {
        Post *post = (Post *) obj;

        values_size += strlen(values_template) - (2 * 3) + strlen(post->title) +
                       strlen(post->description) + sizeof(int) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, post->title, post->description, post->user_id);

    } else if (type == TOKEN_TYPE) {
        Token *token = (Token *) obj;

        values_size += strlen(values_template) - (2 * 2) + strlen(token->token) + sizeof(int) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, token->token, token->user_id);
    } else if (type == USER_TYPE) {
        User *user = (User *) obj;

        values_size += strlen(values_template) - (2 * 2) + strlen(user->username) + strlen(user->password) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, user->username, user->password);
    } else {
        *msg = "Invalid insert type.";
        return 1;
    }

    char *buffer_template = "INSERT INTO %s (%s) VALUES (%s)";

    size_t buffer_size = strlen(buffer_template) - (2 * 3) + strlen(table) + strlen(columns) + values_size + 1;

    char *buffer = malloc(buffer_size);
    memset(buffer, 0, buffer_size);

    sprintf(buffer, buffer_template, table, columns, values);

    return sqlite3_exec(db_connection, buffer, callback, ptr, msg);
}

int update_query(int type, const char *column, const char *value, const void *obj, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg) {
    const char *table = get_table(type, msg);
    if (table == NULL) {
        return 1;
    }

    const char *columns = get_columns(type, msg);
    if (columns == NULL) {
        return 1;
    }

    const char *values_template = get_value_template(type, msg);
    if (values_template == NULL) {
        return 1;
    }

    char *values = 0;
    size_t values_size = 0;

    if (type == POST_TYPE) {
        Post *post = (Post *) obj;

        values_size += strlen(values_template) - (2 * 3) + strlen(post->title) +
                       strlen(post->description) + sizeof(int) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, post->title, post->description, post->user_id);

    } else if (type == TOKEN_TYPE) {
        Token *token = (Token *) obj;

        values_size += strlen(values_template) - (2 * 2) + strlen(token->token) + sizeof(int) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, token->token, token->user_id);
    } else if (type == USER_TYPE) {
        User *user = (User *) obj;

        values_size += strlen(values_template) - (2 * 2) + strlen(user->username) + strlen(user->password) + 1;
        values = malloc(values_size);
        memset(values, 0, values_size);

        sprintf(values, values_template, user->username, user->password);
    } else {
        *msg = "Invalid insert type.";
        return 1;
    }

    char *buffer_template = "UPDATE %s SET (%s) = (%s) WHERE %s = '%s'";

    size_t buffer_size = strlen(buffer_template) - (2 * 5) + strlen(table) + strlen(columns) + values_size +
                         strlen(column) + strlen(value) + 1;

    char *buffer = malloc(buffer_size);
    memset(buffer, 0, buffer_size);

    sprintf(buffer, buffer_template, table, columns, values, column, value);

    return sqlite3_exec(db_connection, buffer, callback, ptr, msg);
}

int delete_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg) {
    const char *buffer_template = "DELETE FROM %s WHERE %s = '%s'";

    const char *table = get_table(type, msg);
    if (table == NULL) {
        return 1;
    }

    size_t buffer_size = strlen(buffer_template) - (2 * 3) + strlen(table) + strlen(column) + strlen(value) + 1;

    char *buffer = malloc(buffer_size);
    memset(buffer, 0, buffer_size);

    sprintf(buffer, buffer_template, table, column, value);

    return sqlite3_exec(db_connection, buffer, callback, ptr, msg);
}
