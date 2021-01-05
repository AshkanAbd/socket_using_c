#include "../Core/Router/router.h"
#include "../controllers/base_controller.h"
#include "../controllers/login_controller.h"

void registerRoutes(Pipeline *pipeline) {
    createAction(pipeline, "/login1", login1);

    createAction(pipeline, "/sign_in", sign_in);
    createAction(pipeline, "/sign_up", sign_up);
}
