/**
 * The file that defines Pipeline struct.
 */
#ifndef SOCKET_SERVER_PIPELINE_H
#define SOCKET_SERVER_PIPELINE_H

#include "../Router/route_template.h"
#include "math.h"
#include <dirent.h>
#include <sys/stat.h>

typedef struct Pipeline Pipeline;

/**
 * The struct that holds dynamic routes and manages the request from start till sends response into client.
 */
struct Pipeline {
    RouteTemplate *templates;
    char *static_files_prefix;

    int route_count;
};

/**
 * Initializes pipeline.
 * @param pipeline
 */
void init_pipeline(Pipeline *pipeline);

/**
 * Sets static routes folder.
 * @param pipeline
 * @param root_dir
 */
void set_root_dir(Pipeline *pipeline, const char *root_dir);

/**
 * Matches request with defined dynamic routes.
 * @param pipeline
 * @param request
 * @return
 */
RouteTemplate *match_request(Pipeline *pipeline, IncomingRequest *request);

/**
 * Executes dynamic route's controller and injects request data into it and return it's response.
 * @param request
 * @param template
 * @return
 */
OutgoingResponse *execute_controller(IncomingRequest *request, RouteTemplate *template);

/**
 * Checks request route with dynamic route.
 * @param template
 * @param request
 * @return
 */
int check_route(RouteTemplate *template, IncomingRequest *request);

/**
 * Checks request action with dynamic route action.
 * @param template
 * @param request
 * @return
 */
int check_action(RouteTemplate *template, IncomingRequest *request);

/**
 * Matches request with static routes.
 * @param pipeline
 * @param request
 * @return
 */
int request_static_files(Pipeline *pipeline, IncomingRequest *request);

/**
 * Serves a static route's file as a response into client.
 * @param response
 * @param pipeline
 * @param request
 * @param client
 */
void serve_static_file(OutgoingResponse *response, Pipeline *pipeline, IncomingRequest *request,
                       Client *client);

/**
 * Waits till client be ready for next packet.
 * @param client
 * @return
 */
int wait_for_client(Client *client);

#endif //SOCKET_SERVER_PIPELINE_H
