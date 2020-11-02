#include "Core/Socket/client.h"
#include "Core/Api/api.h"

void login_ok();

void login_invalid_action();

void login_not_found();

int main() {
    login_ok();

    login_invalid_action();

    login_not_found();
}

void login_ok() {
    struct IncomingResponse *response = api_read("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void login_invalid_action() {
    struct IncomingResponse *response = api_delete("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void login_not_found() {
    struct IncomingResponse *response = api_delete("/login1", NULL, 0);

    printf("%s\n", response_to_str(response));
}
