#include "post_controller.h"

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

OutgoingResponse *post_list(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    int posts_count = 200;

    char *posts_count_sql = "SELECT COUNT() FROM posts";
    char *db_msg = 0;
    if (sqlite3_exec(db_connection, posts_count_sql, posts_count_callback, &posts_count, &db_msg)) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    int posts_index = 0;
    Post *posts[posts_count];
    for (int i = 0; i < posts_count; ++i) {
        posts[i] = malloc(sizeof(Post));
    }
    void *ptr = malloc((2 * sizeof(int)) + (posts_count * sizeof(Post)));
    memset(ptr, 0, (2 * sizeof(int)) + (posts_count * sizeof(Post)));

    memcpy(ptr, &posts_index, sizeof(int));
    memcpy(ptr + sizeof(int), &posts_count, sizeof(int));
    memcpy(ptr + (2 * sizeof(int)), posts, posts_count * sizeof(Post));

    char *get_posts_sql = "SELECT id,title,created_at FROM posts;";
    if (sqlite3_exec(db_connection, get_posts_sql, get_posts_callback, ptr, &db_msg)) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    init_ok(response, ptr, (int) ((2 * sizeof(int)) + (posts_count * sizeof(Post))));
    return response;
}
