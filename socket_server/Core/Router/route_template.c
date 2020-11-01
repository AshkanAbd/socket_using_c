#include "route_template.h"

void initRouteTemplate(struct RouteTemplate *template, int action, char *route,
                       struct OutgoingResponse *(*func)(void *)) {
    template->action = action;

    template->route = malloc(strlen(route));
    memcpy(template->route, route, strlen(route));

    template->func = func;
}
