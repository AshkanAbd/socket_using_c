#include "router.h"

void readAction(struct RouteTemplate *templates, char *route) {
    initRouteTemplate(templates, REQUEST_READ, route);
}

void createAction(struct RouteTemplate *templates, char *route) {
    initRouteTemplate(templates, REQUEST_CREATE, route);
}

void updateAction(struct RouteTemplate *templates, char *route) {
    initRouteTemplate(templates, REQUEST_UPDATE, route);
}

void deleteAction(struct RouteTemplate *templates, char *route) {
    initRouteTemplate(templates, REQUEST_DELETE, route);
}