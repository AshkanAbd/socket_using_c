#include "incoming_response.h"

void init(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->data_size = data_size - 2;

    response->data = malloc(data_size - 2);
    memcpy(response->data, data + 2, data_size - 2);
}

void init_ok(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_OK;

    init(response, data, data_size);
}

void init_not_found(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_NOT_FOUND;

    init(response, data, data_size);
}

void init_bad_request(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_BAD_REQUEST;

    init(response, data, data_size);
}

void init_invalid_action(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_INVALID_ACTION;

    init(response, data, data_size);
}

void init_server_error(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_SERVER_ERROR;

    init(response, data, data_size);
}

void init_invalid_syntax(struct IncomingResponse *response, void *data, unsigned long long int data_size) {
    response->status = RESPONSE_INVALID_SYNTAX;

    init(response, data, data_size);
}

char *response_to_str(struct IncomingResponse *response) {
    char *action_str = "";
    switch (response->status) {
        case RESPONSE_OK:
            action_str = "OK: ";
            break;
        case RESPONSE_NOT_FOUND:
            action_str = "NotFound: ";
            break;
        case RESPONSE_BAD_REQUEST:
            action_str = "BadRequest: ";
            break;
        case RESPONSE_INVALID_ACTION:
            action_str = "InvalidAction: ";
            break;
        case RESPONSE_SERVER_ERROR:
            action_str = "ServerError: ";
            break;
        case RESPONSE_INVALID_SYNTAX:
            action_str = "InvalidSyntax: ";
            break;
    }

    int response_length = response->data_size + 1;
    char *data_str = malloc(response_length);
    memset(data_str, 0, response_length);
    memcpy(data_str, response->data, response->data_size);
    if (strlen(data_str) == 0) {
        data_str = "<content empty>";
    }

    char *response_str = malloc(strlen(action_str) + strlen(data_str) + 1);
    memset(response_str, 0, strlen(action_str) + strlen(data_str) + 1);
    memcpy(response_str, action_str, strlen(action_str));
    memcpy(response_str + strlen(action_str), data_str, strlen(data_str));

    return response_str;
}

void create_full_dir(const char *dir) {
    register int i;
    int pre_index = 0;
    int temp_size = 0;
    char *temp = malloc(temp_size);
    for (i = 0; i < (int) strlen(dir); i++) {
        if (i != 0 && *(dir + i) == '/') {
            temp = realloc(temp, temp_size + (i - pre_index + 2));
            memset(temp + temp_size, 0, temp_size + (i - pre_index + 2));
            memcpy(temp + temp_size, dir + pre_index, i - pre_index);
            _mkdir(temp);
            temp_size += (i - pre_index);
            *(temp + temp_size) = '/';
            temp_size++;
            pre_index = i + 1;
        }
    }
}

char *response_to_file(struct IncomingResponse *response, const char *filepath, const char *filename) {
    char *action_str = "";
    switch (response->status) {
        case RESPONSE_OK:
            action_str = "OK: ";
            break;
        case RESPONSE_NOT_FOUND:
            action_str = "NotFound: ";
            break;
        case RESPONSE_BAD_REQUEST:
            action_str = "BadRequest: ";
            break;
        case RESPONSE_INVALID_ACTION:
            action_str = "InvalidAction: ";
            break;
        case RESPONSE_SERVER_ERROR:
            action_str = "ServerError: ";
            break;
        case RESPONSE_INVALID_SYNTAX:
            action_str = "InvalidSyntax: ";
            break;
    }

    char *fixed_filepath;
    if (*(filepath + strlen(filepath) - 1) != '/') {
        fixed_filepath = malloc(strlen(filepath) + 2);
        memset(fixed_filepath, 0, strlen(filepath) + 2);
        memcpy(fixed_filepath, filepath, strlen(filepath));
        *(fixed_filepath + strlen(filepath)) = '/';
    } else {
        fixed_filepath = malloc(strlen(filepath) + 1);
        memset(fixed_filepath, 0, strlen(filepath) + 1);
        memcpy(fixed_filepath, filepath, strlen(filepath));
    }

    create_full_dir(fixed_filepath);

    char *absolute_path = malloc(strlen(fixed_filepath) + strlen(filename) + 1);
    memset(absolute_path, 0, strlen(fixed_filepath) + strlen(filename) + 1);

    memcpy(absolute_path, fixed_filepath, strlen(fixed_filepath));
    memcpy(absolute_path + strlen(fixed_filepath), filename, strlen(filename));

    FILE *f = fopen(absolute_path, "wb");
    fwrite(response->data, sizeof(char), response->data_size, f);
    fclose(f);

    char *result_str = malloc(strlen(action_str) + strlen(absolute_path) + 1);
    memset(result_str, 0, strlen(action_str) + strlen(absolute_path) + 1);

    memcpy(result_str, action_str, strlen(action_str));
    memcpy(result_str + strlen(action_str), absolute_path, strlen(absolute_path));

    return result_str;
}

char *response_to_file_single_path(struct IncomingResponse *response, const char *filename) {
    char *action_str = "";
    switch (response->status) {
        case RESPONSE_OK:
            action_str = "OK: ";
            break;
        case RESPONSE_NOT_FOUND:
            action_str = "NotFound: ";
            break;
        case RESPONSE_BAD_REQUEST:
            action_str = "BadRequest: ";
            break;
        case RESPONSE_INVALID_ACTION:
            action_str = "InvalidAction: ";
            break;
        case RESPONSE_SERVER_ERROR:
            action_str = "ServerError: ";
            break;
        case RESPONSE_INVALID_SYNTAX:
            action_str = "InvalidSyntax: ";
            break;
    }

    create_full_dir(filename);

    char *absolute_path = malloc(strlen(filename) + 1);
    memset(absolute_path, 0, strlen(filename) + 1);

    memcpy(absolute_path, filename, strlen(filename));

    FILE *f = fopen(absolute_path, "wb");
    fwrite(response->data, sizeof(char), response->data_size, f);
    fclose(f);

    char *result_str = malloc(strlen(action_str) + strlen(absolute_path) + 1);
    memset(result_str, 0, strlen(action_str) + strlen(absolute_path) + 1);

    memcpy(result_str, action_str, strlen(action_str));
    memcpy(result_str + strlen(action_str), absolute_path, strlen(absolute_path));

    return result_str;
}
