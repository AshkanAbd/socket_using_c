#ifndef SOCKET_SERVER_OUTGOING_RESPONSE_H
#define SOCKET_SERVER_OUTGOING_RESPONSE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>

#define RESPONSE_OK 1
#define RESPONSE_NOT_FOUND 2
#define RESPONSE_BAD_REQUEST 3
#define RESPONSE_INVALID_ACTION 4
#define RESPONSE_SERVER_ERROR 5
#define RESPONSE_INVALID_SYNTAX 6

struct IncomingResponse {
    int status;
    void *data;
    unsigned long long int data_size;
};

void init(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_ok(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_not_found(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_bad_request(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_invalid_action(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_server_error(struct IncomingResponse *response, void *data, unsigned long long int data_size);

void init_invalid_syntax(struct IncomingResponse *response, void *data, unsigned long long int data_size);

char *response_to_str(struct IncomingResponse *response);

char *response_to_file(struct IncomingResponse *response, const char *filepath, const char *filename);

char *response_to_file_single_path(struct IncomingResponse *response, const char *filename);

char *get_action_str(struct IncomingResponse *response);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
