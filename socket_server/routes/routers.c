#include "../Core/Router/router.h"
#include "../controllers/controllers.h"

void registerRoutes(Pipeline *pipeline) {
    createAction(pipeline, "/sign_in", sign_in);
    createAction(pipeline, "/sign_up", sign_up);

    readAction(pipeline, "/post_list", post_list);
    readAction(pipeline, "/get_post", get_post);
    createAction(pipeline, "/create_post", create_post);
    updateAction(pipeline, "/update_post", update_post);
}
