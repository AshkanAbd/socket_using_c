#ifndef SOCKET_SERVER_PIPELINE_H
#define SOCKET_SERVER_PIPELINE_H

#include "../Router/router.h"
#include "../Router/route_template.h"

struct Pipeline {
    struct RouteTemplate *templates;
};

void init_pipeline(struct Pipeline *pipeline);

#endif //SOCKET_SERVER_PIPELINE_H
