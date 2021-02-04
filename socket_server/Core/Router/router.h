/**
 * The file that defines dynamic route's functions.
 */
#ifndef SOCKET_SERVER_ROUTER_H
#define SOCKET_SERVER_ROUTER_H

#include "../Pipeline/pipeline.h"

/**
 * The function that dynamic routes should be defines in it.
 * Define your dynamic routes in this function.
 * @param pipeline
 */
void registerRoutes(Pipeline *pipeline);

/**
 * The function that defines a GET action dynamic route.
 * @param pipeline
 * @param route
 * @param func
 */
void readAction(Pipeline *pipeline, char *route,
                OutgoingResponse *(*func)(char **, int, char **, int));

/**
 * The function that defines a POST action dynamic route.
 * @param pipeline
 * @param route
 * @param func
 */
void createAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

/**
 * The function that defines a PUT action dynamic route.
 * @param pipeline
 * @param route
 * @param func
 */
void updateAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

/**
 * The function that defines a DELETE action dynamic route.
 * @param pipeline
 * @param route
 * @param func
 */
void deleteAction(Pipeline *pipeline, char *route,
                  OutgoingResponse *(*func)(char **, int, char **, int));

#endif //SOCKET_SERVER_ROUTER_H
