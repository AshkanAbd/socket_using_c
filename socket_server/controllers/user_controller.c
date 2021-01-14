#include "controllers.h"

static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generate_token(char **output, int length) {
    *output = malloc(length + 1);
    memset(*output, 0, length + 1);

    srand((unsigned) time(NULL) * getpid());

    for (int i = 0; i < length; ++i) {
        *((*output) + i) = alphanum[rand() % (strlen(alphanum) - 1)];
    }
}

OutgoingResponse *sign_in(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    char *username = NULL;
    char *password = NULL;
    int index = 0;
    for (int i = 0; i < request->body_size; ++i) {
        if (*((char *) (request->body + i)) == 0x1E) {
            if (username == NULL) {
                username = malloc(i - index + 1);
                memset(username, 0, i - index + 1);
                memcpy(username, request->body + index, i - index);
            } else if (password == NULL) {
                password = malloc(i - index + 1);
                memset(password, 0, i - index + 1);
                memcpy(password, request->body + index, i - index);
            }
            index = i + 1;
        }
    }

    User *user = NULL;
    char *db_msg = 0;
    if (search_query(USER_TYPE, "username", username, &user,
                     find_user_by_username_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (user == NULL) {
        char *msg = "User notfound.";
        init_bad_request(response, msg, (int) strlen(msg) + 1);
        return response;
    }

    if (strcmp(user->password, password) != 0) {
        char *msg = "Invalid password.";
        init_bad_request(response, msg, (int) strlen(msg) + 1);
        return response;
    }

    char *generated_token = 0;
    generate_token(&generated_token, 40);

    Token *token = malloc(sizeof(Token));
    memset(token, 0, sizeof(Token));
    init_token(token, generated_token, user->id);

    if (insert_query(TOKEN_TYPE, token, NULL, 0, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    init_ok(response, generated_token, (int) strlen(generated_token) + 1);
    return response;
}

OutgoingResponse *sign_up(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    char *username = NULL;
    char *password = NULL;
    int index = 0;
    for (int i = 0; i < request->body_size; ++i) {
        if (*((char *) (request->body + i)) == 0x1E) {
            if (username == NULL) {
                username = malloc(i - index + 1);
                memset(username, 0, i - index + 1);
                memcpy(username, request->body + index, i - index);
            } else if (password == NULL) {
                password = malloc(i - index + 1);
                memset(password, 0, i - index + 1);
                memcpy(password, request->body + index, i - index);
            }
            index = i + 1;
        }
    }

    User *user = NULL;
    char *db_msg = 0;
    if (search_query(USER_TYPE, "username", username, &user,
                     find_user_by_username_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (user != NULL) {
        char *msg = "User exists with given username. Please sign in or user an other username.";
        init_bad_request(response, msg, (int) strlen(msg) + 1);
        return response;
    }

    user = malloc(sizeof(User));
    memset(user, 0, sizeof(User));
    init_user(user, username, password);

    if (insert_query(USER_TYPE, user, NULL, 0, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    if (search_query(USER_TYPE, "username", username, &user,
                     find_user_by_username_callback, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    char *generated_token = 0;
    generate_token(&generated_token, 40);

    Token *token = malloc(sizeof(Token));
    memset(token, 0, sizeof(Token));
    init_token(token, generated_token, user->id);

    if (insert_query(TOKEN_TYPE, token, NULL, 0, &db_msg) != SQLITE_OK) {
        init_server_error(response, db_msg, (int) strlen(db_msg) + 1);
        return response;
    }

    init_ok(response, generated_token, (int) strlen(generated_token) + 1);
    return response;
}
