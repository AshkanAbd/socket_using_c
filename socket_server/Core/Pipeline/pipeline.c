#include "pipeline.h"

void init_pipeline(struct Pipeline *pipeline) {
    pipeline->templates = malloc(1024 * sizeof(struct RouteTemplate));
    memset(pipeline->templates, 0, 1024 * sizeof(struct RouteTemplate));

    registerRoutes(pipeline->templates);
}