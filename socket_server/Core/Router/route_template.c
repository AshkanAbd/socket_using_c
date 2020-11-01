#include "route_template.h"

void initRouteTemplate(struct RouteTemplate *template, int action, char *route,
                       struct OutgoingResponse *(*func)(struct IncomingRequest *request)) {
    template->action = action;

    template->route = malloc(strlen(route));
    memcpy(template->route, route, strlen(route));

    template->func = func;
}
