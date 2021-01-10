#include "auth_api.h"

int server_port;
char *server_ip;

void sign_in_api(const char *username, const char *password, void callback(IncomingResponse *, void *), void *ptr) {
    char *params = malloc(strlen(username) + 1 + strlen(password) + 2);
    memset(params, 0, strlen(username) + 1 + strlen(password) + 2);
    memcpy(params, username, strlen(username));
    memcpy(params + strlen(username) + 1, password, strlen(password));
    *(params + strlen(username)) = 0x1E;
    *(params + strlen(username) + 1 + strlen(password)) = 0x1E;

    IncomingResponse *response = api_create("/sign_in", NULL, 0, params, (int) strlen(params),
                                            server_ip, server_port);

    callback(response, ptr);
}
