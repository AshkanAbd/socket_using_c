#include "interface/interface.h"

void login_ok();

void static_file();

void login_invalid_action();

void login_not_found();

int main() {
    while (1) {
        handle_response(build_request());
        printf("More request?(Y/n) ");
        if (getchar() != 'y') {
            break;
        }
        getchar();
    }
//    login_ok();
//
//    static_file();
//
//    login_invalid_action();
//
//    login_not_found();
}

void login_ok() {
    struct IncomingResponse *response = api_read("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void static_file() {
    struct IncomingResponse *response = api_read("/1.jpg", NULL, 0);
    printf("%d in static file\n", response->status);
    if (response->status == RESPONSE_NOT_FOUND)
        return;
    response_to_file(response, "1.jpg");
}

void login_invalid_action() {
    struct IncomingResponse *response = api_delete("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void login_not_found() {
    struct IncomingResponse *response = api_delete("/login1", NULL, 0);

    printf("%s\n", response_to_str(response));
}
