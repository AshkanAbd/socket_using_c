#include "post.h"

void init_post_full(Post *post, int id, char *title, char *description, int user_id,
                    char *created_at, char *updated_at) {
    post->id = id;

    post->user_id = user_id;

    set_post_column(&post->title, title, 0);

    set_post_column(&post->description, description, 0);

    set_post_column(&post->created_at, created_at, 0);

    set_post_column(&post->updated_at, updated_at, 0);
}

void init_post(Post *post, char *title, char *description, int user_id) {
    post->user_id = user_id;

    set_post_column(&post->title, title, 0);

    set_post_column(&post->description, description, 0);
}

void set_post_column(char **column, const char *value, int with_free) {
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

int insert_post(Post *post, int (*callback)(void *, int, char **, char **), char **msg) {
    if (post->title == NULL) {
        *msg = "title is null";
        return 0;
    }

    if (post->description == NULL) {
        *msg = "description is null";
        return 0;
    }

    if (post->user_id == 0) {
        *msg = "user_id is not valid";
        return 0;
    }

    char *user_id_char = malloc(sizeof(int) + 1);
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(post->user_id, user_id_char, 10);

    char *base_insert_sql = "INSERT INTO posts (title, description, user_id) VALUES (";
    size_t custom_insert_sql_size = strlen(base_insert_sql) + 1 + strlen(post->title) +
                                    3 + strlen(post->description) + 3 + strlen(user_id_char) + 3;
    char *custom_insert_sql = malloc(custom_insert_sql_size);
    memset(custom_insert_sql, 0, custom_insert_sql_size);
    memcpy(custom_insert_sql, base_insert_sql, strlen(base_insert_sql));

    *(custom_insert_sql + strlen(base_insert_sql)) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1, post->title, strlen(post->title));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title)) = '\'';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 1) = ',';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 2) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3,
           post->description, strlen(post->description));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description)) = '\'';


    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description) + 1) = ',';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description) + 2) = '\'';
    memcpy(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description) + 3,
           user_id_char, strlen(user_id_char));
    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description) + 3 +
      strlen(user_id_char)) = '\'';

    *(custom_insert_sql + strlen(base_insert_sql) + 1 + strlen(post->title) + 3 + strlen(post->description) + 3 +
      strlen(user_id_char) + 1) = ')';

    return sqlite3_exec(db_connection, custom_insert_sql, callback, 0, msg);
}