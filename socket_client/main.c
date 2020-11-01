#include "Core/Socket/client.h"
#include "Core/Api/api.h"

void login();

void logout();

int main() {
    login();

    logout();
}

void login() {
    struct IncomingResponse *response = read_api("/login", NULL, 0);

    if (response->status == RESPONSE_OK) {
        char *data_str = malloc(response->data_size);
        memset(data_str, 0, response->data_size);
        memcpy(data_str, response->data, response->data_size);

        printf("%s\n", data_str);
    } else if (response->status == RESPONSE_NOT_FOUND) {
        printf("route notfound\n");
    }
}

void logout() {
    struct IncomingResponse *response = read_api("/logout", NULL, 0);

    if (response->status == RESPONSE_OK) {
        char *data_str = malloc(response->data_size);
        memset(data_str, 0, response->data_size);
        memcpy(data_str, response->data, response->data_size);

        printf("%s\n", data_str);
    } else if (response->status == RESPONSE_NOT_FOUND) {
        printf("route notfound\n");
    }
}
