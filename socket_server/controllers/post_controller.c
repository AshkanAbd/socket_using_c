#include "controllers.h"

void put_separator(void *data, size_t *data_index) {
    char *data_char = (char *) data;
    *(data_char + *data_index) = 0x1E;
    *data_index += 1;
}

void authorize_user(IncomingRequest *request, OutgoingResponse *response, Token **token, int token_size) {
    if (request->param_size == 0) {
        init_bad_request(response, "Unauthorized", 12);
        return;
    }

    char *token_char = malloc(token_size + 1);
    memset(token_char, 0, token_size + 1);
    memcpy(token_char, request->param, token_size);

    char *db_msg = 0;
    if (search_query(TOKEN_TYPE, "token", token_char, token, get_token_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return;
    }

    if (token == NULL) {
        init_bad_request(response, "Unauthorized", 12);
        return;
    }
}

void prepare_one_post_response(char **data, size_t *data_size, Post *post, User *user) {
    char *post_id_char = malloc(sizeof(int) + 1);
    memset(post_id_char, 0, sizeof(int) + 1);
    itoa(post->id, post_id_char, 10);

    char *user_id_char = malloc(sizeof(int) + 1);
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(user->id, user_id_char, 10);

    size_t data_index = 0;
    (*data_size) += sizeof(int);
    (*data_size)++;
    (*data_size) += strlen(post->title);
    (*data_size)++;
    (*data_size) += strlen(post->description);
    (*data_size)++;
    (*data_size) += strlen(post->created_at);
    (*data_size)++;
    (*data_size) += sizeof(int);
    (*data_size)++;
    (*data_size) += strlen(user->username);
    (*data_size)++;

    *data = malloc(*data_size);
    memset(*data, 0, *data_size);

    memcpy(*data, post_id_char, sizeof(int));
    data_index += sizeof(int);
    put_separator(*data, &data_index);

    memcpy((*data) + data_index, post->title, strlen(post->title));
    data_index += strlen(post->title);
    put_separator(*data, &data_index);

    memcpy((*data) + data_index, post->description, strlen(post->description));
    data_index += strlen(post->description);
    put_separator(*data, &data_index);

    memcpy((*data) + data_index, post->created_at, strlen(post->created_at));
    data_index += strlen(post->created_at);
    put_separator(*data, &data_index);

    memcpy((*data) + data_index, user_id_char, sizeof(int));
    data_index += sizeof(int);
    put_separator(*data, &data_index);

    memcpy((*data) + data_index, user->username, strlen(user->username));
    data_index += strlen(user->username);
    put_separator(*data, &data_index);

    free(user_id_char);
    free(post_id_char);
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

    char *get_posts_sql = "SELECT id,title,created_at FROM posts ORDER BY created_at DESC, id DESC";
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

OutgoingResponse *get_post(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    char *post_id_char = malloc(request->param_size + 1);
    memset(post_id_char, 0, request->param_size + 1);
    memcpy(post_id_char, request->param, request->param_size);

    Post *post = NULL;
    char *db_msg = 0;
    if (search_query(POST_TYPE, "id", post_id_char, &post, find_post_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (post == NULL) {
        init_not_found(response, "Post notfound", 13);
        return response;
    }

    char *user_id_char = malloc(sizeof(int) + 1);
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(post->user_id, user_id_char, 10);

    User *user = NULL;
    db_msg = 0;
    if (search_query(USER_TYPE, "id", user_id_char, &user, find_user_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    free(post_id_char);
    free(user_id_char);

    char *data = 0;
    size_t data_size = 1;

    prepare_one_post_response(&data, &data_size, post, user);

    init_ok(response, data, data_size);
    return response;
}

OutgoingResponse *create_post(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    int token_size = 0;
    while (*((char *) request->param + token_size) != 0x1E) {
        token_size++;
        if (token_size >= request->param_size) {
            break;
        }
    }

    Token *token = NULL;
    char *db_msg = NULL;
    authorize_user(request, response, &token, token_size);
    if (response->status != 0) {
        return response;
    }

    char *post_title = NULL;
    char *post_description = NULL;
    int index = 0;
    for (int i = 0; i < request->body_size; ++i) {
        if (*((char *) (request->body + i)) == 0x1E) {
            if (post_title == NULL) {
                post_title = malloc(i - index + 1);
                memset(post_title, 0, i - index + 1);
                memcpy(post_title, request->body + index, i - index);
            } else if (post_description == NULL) {
                post_description = malloc(i - index + 1);
                memset(post_description, 0, i - index + 1);
                memcpy(post_description, request->body + index, i - index);
            }
            index = i + 1;
        }
    }

    Post *post = malloc(sizeof(Post));
    memset(post, 0, sizeof(Post));

    init_post(post, post_title, post_description, token->user_id);
    if (insert_query(POST_TYPE, post, NULL, 0, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (sqlite3_exec(db_connection, "SELECT * FROM posts ORDER BY id DESC LIMIT 1", get_new_post_callback, &post,
                     &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    char *post_id_char = malloc(sizeof(int) + 1);
    memset(post_id_char, 0, sizeof(int) + 1);
    itoa(post->id, post_id_char, 10);

    char *user_id_char = malloc(sizeof(int) + 1);
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(post->user_id, user_id_char, 10);

    User *user = NULL;
    db_msg = 0;
    if (search_query(USER_TYPE, "id", user_id_char, &user, find_user_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    free(post_id_char);
    free(user_id_char);

    char *data = 0;
    size_t data_size = 1;

    prepare_one_post_response(&data, &data_size, post, user);

    init_ok(response, data, data_size);
    return response;
}

OutgoingResponse *update_post(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    int token_size = 0;
    while (*((char *) request->param + token_size) != 0x1E) {
        token_size++;
        if (token_size >= request->param_size) {
            init_invalid_syntax(response, NULL, 0);
            return response;
        }
    }

    Token *token = NULL;
    char *db_msg = NULL;
    authorize_user(request, response, &token, token_size);
    if (response->status != 0) {
        return response;
    }

    token_size++;
    int id_size = 0;
    while (*((char *) request->param + token_size + id_size) != 0x1E) {
        id_size++;
        if (token_size + id_size >= request->param_size) {
            init_invalid_syntax(response, NULL, 0);
            return response;
        }
    }

    char *post_id_char = malloc(id_size + 1);
    memset(post_id_char, 0, id_size + 1);
    memcpy(post_id_char, request->param + token_size, id_size);

    Post *post = NULL;
    if (search_query(POST_TYPE, "id", post_id_char, &post, find_post_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, strlen(db_msg));
        return response;
    }

    if (post->user_id != token->user_id) {
        init_bad_request(response, "You can't edit other people post.", 33);
        return response;
    }

    char *post_title = NULL;
    char *post_description = NULL;
    int index = 0;
    for (int i = 0; i < request->body_size; ++i) {
        if (*((char *) (request->body + i)) == 0x1E) {
            if (post_title == NULL) {
                post_title = malloc(i - index + 1);
                memset(post_title, 0, i - index + 1);
                memcpy(post_title, request->body + index, i - index);
            } else if (post_description == NULL) {
                post_description = malloc(i - index + 1);
                memset(post_description, 0, i - index + 1);
                memcpy(post_description, request->body + index, i - index);
            }
            index = i + 1;
        }
    }

    set_post_column(&post->title, post_title, 1);
    set_post_column(&post->description, post_description, 1);

    if (update_query(POST_TYPE, "id", post_id_char, post, NULL, 0, &db_msg)) {
        init_bad_request(response, "You can't edit other people post.", 33);
        return response;
    }

    char *user_id_char = malloc(sizeof(int) + 1);
    memset(user_id_char, 0, sizeof(int) + 1);
    itoa(post->user_id, user_id_char, 10);

    User *user = NULL;
    db_msg = 0;
    if (search_query(USER_TYPE, "id", user_id_char, &user, find_user_by_id_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    free(post_id_char);
    free(user_id_char);

    char *data = 0;
    size_t data_size = 1;

    prepare_one_post_response(&data, &data_size, post, user);

    init_ok(response, data, data_size);
    return response;
}
