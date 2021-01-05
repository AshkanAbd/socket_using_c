#include "route_template.h"

void initRouteTemplate(RouteTemplate *template, int action, char *route,
                       OutgoingResponse *(*func)(IncomingRequest *request)) {
    template->action = action;

    template->route = malloc(strlen(route) + 1);
    memset(template->route, 0, strlen(route) + 1);
    memcpy(template->route, route, strlen(route));

    template->func = func;
}
