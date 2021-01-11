#include "interface.h"

char *token;

void sign_up_callback(IncomingResponse *response, void *ptr) {
    if (response->status == RESPONSE_OK) {
        printf("Sign up successful\n");
        change_life_cycle_status(STATUS_POST_ACTION);

        token = malloc(response->data_size + 1);
        memset(token, 0, response->data_size + 1);
        memcpy(token, response->data, response->data_size);
    } else {
        print_error_repose(response);
        change_life_cycle_status(STATUS_START);
    }
}

void sign_up_status() {
    printf("Fill information for sign up\n");

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

    printf("Sending sign up request, please wait...\n");
    sign_up_api(username, password, sign_up_callback, NULL);
    free(username);
    free(password);
}

