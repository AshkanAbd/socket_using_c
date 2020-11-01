#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "route_template.h"
#include "../IO/incoming_request.h"

void registerRoutes(struct RouteTemplate *templates);

void readAction(struct RouteTemplate *templates, char *route);

void createAction(struct RouteTemplate *templates, char *route);

void updateAction(struct RouteTemplate *templates, char *route);

void deleteAction(struct RouteTemplate *templates, char *route);

#endif //SOCKET_SERVER_ROUTER_H
