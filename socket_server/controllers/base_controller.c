#include "base_controller.h"

OutgoingResponse *login1(IncomingRequest *request) {
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));

    printf("Client query parameters:<%s>\n", request->param);
    printf("Client body:<%s>\n", request->body);

    char *hi_str = "login successful";

    init_ok(response, hi_str, strlen(hi_str) + 1);
    return response;
}
