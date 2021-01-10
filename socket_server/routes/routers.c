#include "../Core/Router/router.h"
#include "../controllers/controllers.h"

void registerRoutes(Pipeline *pipeline) {
    createAction(pipeline, "/sign_in", sign_in);
    createAction(pipeline, "/sign_up", sign_up);

    readAction(pipeline, "/post", post_list);
}
