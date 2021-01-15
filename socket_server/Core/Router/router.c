#include "router.h"

void readAction(Pipeline *pipeline, char *route,
                OutgoingResponse *(*func)(char **, int, char **, int)) {
    initRouteTemplate((pipeline->templates + pipeline->route_count++), REQUEST_READ, route, func);
}

void createAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int)) {
    initRouteTemplate((pipeline->templates + pipeline->route_count++), REQUEST_CREATE, route, func);
}

void updateAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int)) {
    initRouteTemplate((pipeline->templates + pipeline->route_count++), REQUEST_UPDATE, route, func);
}

void deleteAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int)) {
    initRouteTemplate((pipeline->templates + pipeline->route_count++), REQUEST_DELETE, route, func);
}