#ifndef SOCKET_SERVER_PIPELINE_H
#define SOCKET_SERVER_PIPELINE_H

#include "../Router/route_template.h"
#include "math.h"
#include <dirent.h>
#include <sys/stat.h>

struct Pipeline {
    struct RouteTemplate *templates;
    char *static_files_prefix;

    int route_count;
};

void init_pipeline(struct Pipeline *pipeline);

void set_root_dir(struct Pipeline *pipeline, const char *root_dir);

struct RouteTemplate *match_request(struct Pipeline *pipeline, struct IncomingRequest *request);

struct OutgoingResponse *execute_controller(struct IncomingRequest *request, struct RouteTemplate *template);

int check_route(struct RouteTemplate *template, struct IncomingRequest *request);

int check_action(struct RouteTemplate *template, struct IncomingRequest *request);

int request_static_files(struct Pipeline *pipeline, struct IncomingRequest *request);

void serve_static_file(struct OutgoingResponse *response, struct Pipeline *pipeline, struct IncomingRequest *request,
                       struct Client *client);

int wait_for_client(struct Client *client);

#endif //SOCKET_SERVER_PIPELINE_H
