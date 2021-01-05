#ifndef SOCKET_SERVER_POST_H
#define SOCKET_SERVER_POST_H

#include "string.h"
#include "stdlib.h"

typedef struct Post Post;

struct Post {
    int id;
    char *title;
    char *description;
    int user_id;
};

void init_post(Post *post, int id, char *title, char *description, int user_id);

void set_post_column(char **column, const char *value);

#endif //SOCKET_SERVER_POST_H
