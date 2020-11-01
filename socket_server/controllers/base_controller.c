#include "base_controller.h"

struct OutgoingResponse *login(struct IncomingRequest *request) {
    struct OutgoingResponse *response = malloc(sizeof(struct OutgoingResponse));
    memset(response, 0, sizeof(struct OutgoingResponse));

    char *hi_str = "login successful";

    init_ok(response, hi_str, strlen(hi_str));
    return response;
}
