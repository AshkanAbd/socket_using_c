/**
 * The file that defines IncomingResponse struct
 */
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

typedef struct IncomingResponse IncomingResponse;

/**
 * The struct that uses to hold parsed response packet from web server.
 */
struct IncomingResponse {
    int status;
    void *data;
    unsigned long long int data_size;
    int port;
    char *ip;
};

/**
 * Sets ip and port of the response.
 * @param response
 * @param ip
 * @param port
 */
void set_port_and_ip(struct IncomingResponse *response, char *ip, int port);

/**
 * Parses the packet to a response.
 * @param response
 * @param data
 * @param data_size
 */
void init(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from OK status.
 * @param response
 * @param data
 * @param data_size
 */
void init_ok(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from NOTFOUND status.
 * @param response
 * @param data
 * @param data_size
 */
void init_not_found(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from BAD REQUEST status.
 * @param response
 * @param data
 * @param data_size
 */
void init_bad_request(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from INVALID ACTION status.
 * @param response
 * @param data
 * @param data_size
 */
void init_invalid_action(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from SERVER ERROR status.
 * @param response
 * @param data
 * @param data_size
 */
void init_server_error(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Parses the packet to a response from INVALID SYNTAX status.
 * @param response
 * @param data
 * @param data_size
 */
void init_invalid_syntax(struct IncomingResponse *response, void *data, unsigned long long int data_size);

/**
 * Extracts response body to a string.
 * @param response
 * @return
 */
char *response_to_str(struct IncomingResponse *response);

/**
 * Extracts response body to a file.
 * @param response
 * @param filepath
 * @param filename
 * @return
 */
char *response_to_file(struct IncomingResponse *response, const char *filepath, const char *filename);

/**
 * Extracts response body to a string.
 * @param response
 * @param filename
 * @return
 */
char *response_to_file_single_path(struct IncomingResponse *response, const char *filename);

/**
 * Extracts response status to a string.
 * @param response
 * @return
 */
char *get_action_str(struct IncomingResponse *response);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
