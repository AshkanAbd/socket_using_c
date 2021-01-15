#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "../Pipeline/pipeline.h"

void registerRoutes(Pipeline *pipeline);

void readAction(Pipeline *pipeline, char *route,
                OutgoingResponse *(*func)(char **, int, char **, int));

void createAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

void updateAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

void deleteAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

#endif //SOCKET_SERVER_ROUTER_H
