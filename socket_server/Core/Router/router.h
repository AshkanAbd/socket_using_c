#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "../Pipeline/pipeline.h"

void registerRoutes(struct Pipeline *pipeline);

void readAction(struct Pipeline *pipeline, char *route,
                struct OutgoingResponse *(*func)(void *));

void createAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(void *));

void updateAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(void *));

void deleteAction(struct Pipeline *pipeline, char *route,
                  struct OutgoingResponse *(*func)(void *));

#endif //SOCKET_SERVER_ROUTER_H
