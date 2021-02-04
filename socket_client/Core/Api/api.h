/**
 * Header file that contains api functions.
 * Api functions use to send request to web server and return response
 */
#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "../IO/incoming_response.h"
#include "../IO/outgoing_request.h"
#include "../Socket/client.h"
#include "../Socket/client_socket.h"

/**
 * Send a request to web server and returns web server response, This function uses by api functions.
 * @param request
 * @param client
 * @return
 */
struct IncomingResponse *send_request(OutgoingRequest *request, Client *client);

/**
 * GET function of api functions, Sends a get request to web server and return response
 * @param route
 * @param param
 * @param param_size
 * @param ip
 * @param port
 * @return
 */
struct IncomingResponse *api_read(char *route, void *param, int param_size, char *ip, int port);

/**
 * POST function of api functions, Sends a get request to web server and return response
 * @param route
 * @param param
 * @param param_size
 * @param body
 * @param body_size
 * @param ip
 * @param port
 * @return
 */
struct IncomingResponse *
api_create(char *route, void *param, int param_size, void *body, int body_size, char *ip, int port);

/**
 * PUT function of api functions, Sends a get request to web server and return response
 * @param route
 * @param param
 * @param param_size
 * @param body
 * @param body_size
 * @param ip
 * @param port
 * @return
 */
struct IncomingResponse *
api_update(char *route, void *param, int param_size, void *body, int body_size, char *ip, int port);

/**
 * DELETE function of api functions, Sends a get request to web server and return response
 * @param route
 * @param param
 * @param param_size
 * @param ip
 * @param port
 * @return
 */
struct IncomingResponse *api_delete(char *route, void *param, int param_size, char *ip, int port);

#endif //SOCKET_CLIENT_API_H
