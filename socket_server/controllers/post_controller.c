#include "controllers.h"

int posts_count_callback(void *ptr, int row_count, char **data, char **columns) {
    int *posts_count = (int *) ptr;

    *posts_count = atoi(data[0]);

    return 0;
}

void put_separator(void *data, size_t *data_index) {
    char *data_char = (char *) data;
//    *((char *) (data + *data_index)) = 0x1E;
    *(data_char + *data_index) = 0x1E;
    *data_index += 1;
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
    if (sqlite3_exec(db_connection, posts_count_sql, posts_count_callback, &posts_count, &db_msg) != SQLITE_OK) {
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
    if (sqlite3_exec(db_connection, get_posts_sql, get_posts_callback, ptr, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    size_t data_size = sizeof(int) + 1;
    size_t data_index = 0;
    for (int i = 0; i < posts_count; ++i) {
        data_size += (sizeof(int) + 1);
        data_size += (strlen((*(posts + i))->title) + 1);
        data_size += (strlen((*(posts + i))->created_at) + 1);
    }

    void *data = malloc(data_size);
    memset(data, 0, data_size);

    char posts_count_char[sizeof(int)];
    itoa(posts_count, posts_count_char, 10);

    memcpy(data, posts_count_char, sizeof(int));
    data_index += sizeof(int);

    put_separator(data, &data_index);

    for (int i = 0; i < posts_count; ++i) {
        char id_char[sizeof(int)];
        itoa((*(posts + i))->id, id_char, 10);

//        memcpy(data + data_index, &(*(posts + i))->id, sizeof(int));
        memcpy(data + data_index, id_char, sizeof(int));
        data_index += sizeof(int);

        put_separator(data, &data_index);

        size_t title_length = strlen((*(posts + i))->title);
        memcpy(data + data_index, (*(posts + i))->title, title_length);
        data_index += title_length;

        put_separator(data, &data_index);

        size_t created_at_length = strlen((*(posts + i))->created_at);
        memcpy(data + data_index, (*(posts + i))->created_at, created_at_length);
        data_index += created_at_length;

        put_separator(data, &data_index);
    }

    init_ok(response, data, data_size);
    return response;
}

int find_post_by_id_callback(void *ptr, int row_count, char **data, char **columns) {
    Post **post = (Post **) ptr;
    *post = malloc(sizeof(Post));
    memset(*post, 0, sizeof(Post));

    init_post_full(*post, atoi(data[0]), data[1], data[2], atoi(data[3]),
                   data[4], data[5]);
    return 0;
}

int find_user_by_id_callback(void *ptr, int row_count, char **data, char **columns) {
    User **user = (User **) ptr;
    *user = malloc(sizeof(User));
    memset(*user, 0, sizeof(User));

    init_user_full(*user, atoi(data[0]), data[1], data[2], data[3], data[4]);
    return 0;
}

OutgoingResponse *get_post(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    char *post_id_char = malloc(request->param_size + 1);
    memset(post_id_char, 0, request->param_size + 1);
    memcpy(post_id_char, request->param, request->param_size);

    Post *post = NULL;
    char *db_msg = 0;
    if (post_search_by_id(post_id_char, &post, find_post_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (post == NULL) {
        init_not_found(response, "Post notfound", 13);
        return response;
    }

    char user_id_char[sizeof(int) + 1];
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(post->user_id, user_id_char, 10);

    User *user = NULL;
    db_msg = 0;
    if (user_search_by_id(user_id_char, &user, find_user_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    size_t data_size = 0;
    size_t data_index = 0;
    data_size += sizeof(int);
    data_size++;
    data_size += strlen(post->title);
    data_size++;
    data_size += strlen(post->description);
    data_size++;
    data_size += strlen(post->created_at);
    data_size++;
    data_size += sizeof(int);
    data_size++;
    data_size += strlen(user->username);
    data_size++;

    char *data = malloc(data_size);
    memset(data, 0, data_size);

    memcpy(data, post_id_char, sizeof(int));
    data_index += sizeof(int);
    put_separator(data, &data_index);

    memcpy(data + data_index, post->title, strlen(post->title));
    data_index += strlen(post->title);
    put_separator(data, &data_index);

    memcpy(data + data_index, post->description, strlen(post->description));
    data_index += strlen(post->description);
    put_separator(data, &data_index);

    memcpy(data + data_index, post->created_at, strlen(post->created_at));
    data_index += strlen(post->created_at);
    put_separator(data, &data_index);

    memcpy(data, user_id_char, sizeof(int));
    data_index += sizeof(int);
    put_separator(data, &data_index);

    memcpy(data + data_index, user->username, strlen(user->username));
    data_index += strlen(user->username);
    put_separator(data, &data_index);

    init_ok(response, data, data_size);
    return response;
}
