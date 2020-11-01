#ifndef SOCKET_SERVER_ROUTE_TEMPLATE_H
#define SOCKET_SERVER_ROUTE_TEMPLATE_H

#include <string.h>
#include <stdlib.h>
#include "../IO/outgoing_response.h"

struct RouteTemplate {
    int action;
    char *route;

    struct OutgoingResponse *(*func)(void *payload);
};

void initRouteTemplate(struct RouteTemplate *template, int action, char *route,
                       struct OutgoingResponse *(*func)(void *));

#endif //SOCKET_SERVER_ROUTE_TEMPLATE_H
