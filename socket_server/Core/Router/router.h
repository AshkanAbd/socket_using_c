#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "../Pipeline/pipeline.h"

void registerRoutes(struct Pipeline *pipeline);

void readAction(struct Pipeline *pipeline, char *route,
                struct OutgoingResponse *(*func)(struct IncomingRequest *request));

void createAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(struct IncomingRequest *request));

void updateAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(struct IncomingRequest *request));

void deleteAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(struct IncomingRequest *request));

#endif //SOCKET_SERVER_ROUTER_H
