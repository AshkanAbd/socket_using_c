#include "post.h"

void init_post(Post *post, int id, char *title, char *description, int user_id) {
    post->id = id;

    post->user_id = id;

    set_post_column(&post->title, title);

    set_post_column(&post->description, description);
}

void set_post_column(char **column, const char *value) {
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
