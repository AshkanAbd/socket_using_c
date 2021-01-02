#ifndef SOCKET_CLIENT_INTERFACE_H
#define SOCKET_CLIENT_INTERFACE_H

#include "../Core/Api/api.h"
#include "../Core/HtmlParser/html_parser.h"

struct IncomingResponse *request_builder();

void response_handler(struct IncomingResponse *response);

#endif //SOCKET_CLIENT_INTERFACE_H
