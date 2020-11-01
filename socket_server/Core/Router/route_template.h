#ifndef SOCKET_SERVER_ROUTE_TEMPLATE_H
#define SOCKET_SERVER_ROUTE_TEMPLATE_H

#include <string.h>
#include <stdlib.h>

struct RouteTemplate {
    int action;
    char *route;
};

void initRouteTemplate(struct RouteTemplate *template, int action, char *route);

#endif //SOCKET_SERVER_ROUTE_TEMPLATE_H
