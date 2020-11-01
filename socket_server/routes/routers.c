#include "../Core/Router/router.h"
#include "../controllers/base_controller.h"

void registerRoutes(struct Pipeline *pipeline) {
    readAction(pipeline, "/hello", sample);
}
