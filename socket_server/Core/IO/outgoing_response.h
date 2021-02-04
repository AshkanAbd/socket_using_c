/**
 * The file that defines OutgoingResposnse.
 */
#ifndef SOCKET_SERVER_OUTGOING_RESPONSE_H
#define SOCKET_SERVER_OUTGOING_RESPONSE_H

#include "../Socket/client.h"

#define RESPONSE_OK 1
#define RESPONSE_NOT_FOUND 2
#define RESPONSE_BAD_REQUEST 3
#define RESPONSE_INVALID_ACTION 4
#define RESPONSE_SERVER_ERROR 5
#define RESPONSE_INVALID_SYNTAX 6

static int MAX = 1024;

typedef struct OutgoingResponse OutgoingResponse;

/**
 * The struct that holds OutgoingResponse data.
 */
struct OutgoingResponse {
    int status;
    void *data;
    int data_size;
};

/**
 * Changes Response max packet size.
 * @param max
 */
void change_max(int max);

/**
 * Initialize OutgoingResponse with OK status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_ok(OutgoingResponse *response, void *data, int data_size);

/**
 * Initialize OutgoingResponse with NOTFOUND status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_not_found(OutgoingResponse *response, void *data, int data_size);

/**
 * Initialize OutgoingResponse with BAD_REQUEST status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_bad_request(OutgoingResponse *response, void *data, int data_size);

/**
 * Initialize OutgoingResponse with INVALID_ACTION status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_invalid_action(OutgoingResponse *response, void *data, int data_size);

/**
 * Initialize OutgoingResponse with SERVER_ERROR status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_server_error(OutgoingResponse *response, void *data, int data_size);

/**
 * Initialize OutgoingResponse with INVALID_SYNTAX status and data.
 * @param response
 * @param data
 * @param data_size
 */
void init_invalid_syntax(OutgoingResponse *response, void *data, int data_size);

/**
 * Combines OutgoingResponse struct into a packet(byte array) and sends it to client.
 * @param response
 * @param client
 * @param final_packet
 */
void send_to_client(OutgoingResponse *response, Client *client, int final_packet);

#endif //SOCKET_SERVER_OUTGOING_RESPONSE_H
