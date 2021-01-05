#ifndef SOCKET_SERVER_PIPELINE_H
#define SOCKET_SERVER_PIPELINE_H

#include "../Router/route_template.h"
#include "math.h"
#include <dirent.h>
#include <sys/stat.h>

typedef struct Pipeline Pipeline;

struct Pipeline {
    RouteTemplate *templates;
    char *static_files_prefix;

    int route_count;
};

void init_pipeline(Pipeline *pipeline);

void set_root_dir(Pipeline *pipeline, const char *root_dir);

RouteTemplate *match_request(Pipeline *pipeline, IncomingRequest *request);

OutgoingResponse *execute_controller(IncomingRequest *request, RouteTemplate *template);

int check_route(RouteTemplate *template, IncomingRequest *request);

int check_action(RouteTemplate *template, IncomingRequest *request);

int request_static_files(Pipeline *pipeline, IncomingRequest *request);

void serve_static_file(OutgoingResponse *response, Pipeline *pipeline, IncomingRequest *request,
                       Client *client);

int wait_for_client(Client *client);

#endif //SOCKET_SERVER_PIPELINE_H
