#ifndef SOCKET_SERVER_PIPELINE_H
#define SOCKET_SERVER_PIPELINE_H

#include "../Router/route_template.h"
#include "../IO/incoming_request.h"

struct Pipeline {
    struct RouteTemplate *templates;

    int route_count;
};

void init_pipeline(struct Pipeline *pipeline);

struct RouteTemplate *match_request(struct Pipeline *pipeline, struct IncomingRequest *request);

struct OutgoingResponse *execute_controller(struct IncomingRequest *request, struct RouteTemplate *template);

int check_route(struct RouteTemplate *template, struct IncomingRequest *request);

int check_action(struct RouteTemplate *template, struct IncomingRequest *request);

#endif //SOCKET_SERVER_PIPELINE_H
