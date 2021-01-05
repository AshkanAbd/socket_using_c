#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "../Pipeline/pipeline.h"

void registerRoutes(Pipeline *pipeline);

void readAction(Pipeline *pipeline, char *route,
                OutgoingResponse *(*func)(IncomingRequest *));

void createAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(IncomingRequest *));

void updateAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(IncomingRequest *));

void deleteAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(IncomingRequest *));

#endif //SOCKET_SERVER_ROUTER_H
