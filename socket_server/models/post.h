#ifndef SOCKET_SERVER_POST_H
#define SOCKET_SERVER_POST_H

#include "string.h"
#include "stdlib.h"
#include "../Core/db/sqlite/migration.h"

typedef struct Post Post;

struct Post {
    int id;
    char *title;
    char *description;
    int user_id;
    char *created_at;
    char *updated_at;
};

void init_post_full(Post *post, int id, char *title, char *description, int user_id,
                    char *created_at, char *updated_at);

void init_post(Post *post, char *title, char *description, int user_id);

void set_post_column(char **column, const char *value, int with_free);

int insert_post(Post *post, int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_POST_H
