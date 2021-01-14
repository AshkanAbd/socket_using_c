#include "callbacks.h"

int posts_count_callback(void *ptr, int row_count, char **data, char **columns) {
    int *posts_count = (int *) ptr;

    *posts_count = atoi(data[0]);

    return 0;
}

int get_posts_callback(void *ptr, int row_count, char **data, char **columns) {
    int *posts_index = (int *) ptr;

    int *posts_count = (int *) (ptr + sizeof(int));

    Post **posts = (Post **) (ptr + (2 * sizeof(int)));

    Post *post = *(posts + *posts_index);

    post->id = atoi(data[0]);
    set_post_column(&post->title, data[1], 0);
    set_post_column(&post->created_at, data[2], 0);
    post->user_id = 0;
    post->description = NULL;
    post->updated_at = NULL;

    (*posts_index)++;
    return 0;
}

int find_post_by_id_callback(void *ptr, int row_count, char **data, char **columns) {
    Post **post = (Post **) ptr;
    *post = malloc(sizeof(Post));
    memset(*post, 0, sizeof(Post));

    init_post_full(*post, atoi(data[0]), data[1], data[2], atoi(data[3]),
                   data[4], data[5]);
    return 0;
}

int get_new_post_callback(void *ptr, int row_count, char **data, char **columns) {
    Post **post = (Post **) ptr;
    *post = malloc(sizeof(Post));
    memset(*post, 0, sizeof(Post));

    init_post_full(*post, atoi(data[0]), data[1], data[2], atoi(data[3]),
                   data[4], data[5]);
    return 0;
}
