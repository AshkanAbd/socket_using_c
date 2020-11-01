#include "router.h"

void readAction(struct RouteTemplate *templates, char *route,
                struct OutgoingResponse *(*func)(void *)) {
    initRouteTemplate(templates, REQUEST_READ, route, func);
}

void createAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *)) {
    initRouteTemplate(templates, REQUEST_CREATE, route, func);
}

void updateAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *)) {
    initRouteTemplate(templates, REQUEST_UPDATE, route, func);
}

void deleteAction(struct RouteTemplate *templates, char *route,
                  struct OutgoingResponse *(*func)(void *)) {
    initRouteTemplate(templates, REQUEST_DELETE, route, func);
}