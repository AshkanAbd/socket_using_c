/**
 * The file that defines RouteTemplate struct.
 */
#ifndef SOCKET_SERVER_ROUTE_TEMPLATE_H
#define SOCKET_SERVER_ROUTE_TEMPLATE_H

#include <stdio.h>
#include "../IO/outgoing_response.h"
#include "../IO/incoming_request.h"

typedef struct RouteTemplate RouteTemplate;

/**
 * The struct that holds a dynamic route.
 */
struct RouteTemplate {
    int action;
    char *route;

    OutgoingResponse *(*func)(char **, int, char **, int);
};

/**
 * Initializes a RouteTemplate struct with given data.
 * @param template
 * @param action
 * @param route
 * @param func
 */
void initRouteTemplate(RouteTemplate *template, int action, char *route,
                       OutgoingResponse *(*func)(char **, int, char **, int));

#endif //SOCKET_SERVER_ROUTE_TEMPLATE_H
