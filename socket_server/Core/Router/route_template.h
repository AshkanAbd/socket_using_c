#ifndef SOCKET_SERVER_ROUTE_TEMPLATE_H
#define SOCKET_SERVER_ROUTE_TEMPLATE_H

#include <stdio.h>
#include "../IO/outgoing_response.h"
#include "../IO/incoming_request.h"

typedef struct RouteTemplate RouteTemplate;

struct RouteTemplate {
    int action;
    char *route;

    OutgoingResponse *(*func)(IncomingRequest *request);
};

void initRouteTemplate(RouteTemplate *template, int action, char *route,
                       OutgoingResponse *(*func)(IncomingRequest *request));

#endif //SOCKET_SERVER_ROUTE_TEMPLATE_H
