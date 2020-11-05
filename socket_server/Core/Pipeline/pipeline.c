#include "pipeline.h"
#include "../Router/router.h"

void init_pipeline(struct Pipeline *pipeline) {
    pipeline->route_count = 0;

    pipeline->templates = malloc(1024 * sizeof(struct RouteTemplate));
    memset(pipeline->templates, 0, 1024 * sizeof(struct RouteTemplate));

    registerRoutes(pipeline);
}

struct RouteTemplate *match_request(struct Pipeline *pipeline, struct IncomingRequest *request) {
    struct RouteTemplate *template = NULL;
    register int i;
    for (i = 0; i < pipeline->route_count; ++i) {
        struct RouteTemplate *tmp = pipeline->templates + i;
        if (check_route(tmp, request)) {
            if (check_action(tmp, request)) {
                return tmp;
            }
            template = tmp;
        }
    }
    return template;
}

int check_route(struct RouteTemplate *template, struct IncomingRequest *request) {
    if (strcmp(template->route, request->route) == 0) {
        return 1;
    }
    return 0;
}

int check_action(struct RouteTemplate *template, struct IncomingRequest *request) {
    if (template->action == request->action) {
        return 1;
    }
    return 0;
}

struct OutgoingResponse *execute_controller(struct IncomingRequest *request, struct RouteTemplate *template) {
    return (*template->func)(request);
}

