#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "route_template.h"
#include "../IO/incoming_request.h"
#include "../IO/outgoing_response.h"

void registerRoutes(struct RouteTemplate *templates);

void readAction(struct RouteTemplate *templates, char *route,
                struct OutgoingResponse *(*func)(void *));

void createAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *));

void updateAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *));

void deleteAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *));

#endif //SOCKET_SERVER_ROUTER_H
