#include "interface.h"

char *token;

void sign_in_callback(IncomingResponse *response, void *ptr) {
    if (response->status == RESPONSE_OK) {
        printf("Sign in successful\n");
        change_life_cycle_status(STATUS_POST_LIST);

        token = malloc(response->data_size + 1);
        memset(token, 0, response->data_size + 1);
        memcpy(token, response->data, response->data_size);
    } else {
        print_error_repose(response);
        change_life_cycle_status(STATUS_START);
    }
}

void sign_in_status() {
    printf("Fill information for sign in\n");

    char c;
    int index = 0;

    char *username = malloc(1024);
    memset(username, 0, 1024);
    printf("Enter username: ");

    while ((c = getchar()) != '\n') {
        *(username + index++) = c;
    }

    char *password = malloc(1024);
    memset(password, 0, 1024);
    printf("Enter password: ");
    index = 0;

    while ((c = getchar()) != '\n') {
        *(password + index++) = c;
    }

    printf("Sending sign in request, please wait...\n");
    sign_in_api(username, password, sign_in_callback, NULL);
}
