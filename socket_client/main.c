#include "interface/interface.h"
#include "Core/HtmlParser/html_parser.h"

void login_ok();

void static_file();

void login_invalid_action();

void login_not_found();

int main() {
//    login_ok();

    static_file();

//    login_invalid_action();
//
//    login_not_found();
}

void login_ok() {
    struct IncomingResponse *response = api_read("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void static_file() {
    struct IncomingResponse *response = api_read("/gta.png", NULL, 0);
    printf("Status %d in static file\n", response->status);
    if (response->status == RESPONSE_NOT_FOUND) {
        printf("static file notfound");
        return;
    }
    printf("%s\n", response_to_file(response, "output/img/", "csgo.png"));
}

void login_invalid_action() {
    struct IncomingResponse *response = api_delete("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void login_not_found() {
    struct IncomingResponse *response = api_delete("/login1", NULL, 0);

    printf("%s\n", response_to_str(response));
}
