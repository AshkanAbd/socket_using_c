#include "base_controller.h"

struct OutgoingResponse *login(struct IncomingRequest *request) {
    struct OutgoingResponse *response = malloc(sizeof(struct OutgoingResponse));
    memset(response, 0, sizeof(struct OutgoingResponse));

    printf("Client query parameters:<%s>\n", request->param);
    printf("Client body:<%s>\n", request->body);

    char *hi_str = "login successful";

    init_ok(response, hi_str, strlen(hi_str) + 1);
    return response;
}
