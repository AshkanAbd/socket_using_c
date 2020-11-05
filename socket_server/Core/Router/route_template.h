#ifndef SOCKET_SERVER_ROUTE_TEMPLATE_H
#define SOCKET_SERVER_ROUTE_TEMPLATE_H

#include <stdio.h>
#include "../IO/outgoing_response.h"
#include "../IO/incoming_request.h"

struct RouteTemplate {
    int action;
    char *route;

    struct OutgoingResponse *(*func)(struct IncomingRequest *request);
};

void initRouteTemplate(struct RouteTemplate *template, int action, char *route,
                       struct OutgoingResponse *(*func)(struct IncomingRequest *request));

#endif //SOCKET_SERVER_ROUTE_TEMPLATE_H
