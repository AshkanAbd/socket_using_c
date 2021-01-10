#include "sign_in_status.h"

char *token;

void sign_in_callback(IncomingResponse *response, void *ptr) {
    int *current_status = (int *) ptr;
    if (response->status == RESPONSE_OK) {
        printf("Sign in successful\n");
        *current_status = STATUS_GET_POST_LIST;

        token = malloc(response->data_size + 1);
        memset(token, 0, response->data_size + 1);
        memcpy(token, response->data, response->data_size);

    } else {
        char *msg = malloc(response->data_size + 1);
        memset(msg, 0, response->data_size + 1);
        memcpy(msg, response->data, response->data_size);
        printf("Error: %s\n", msg);
        *current_status = STATUS_START;
    }
}

void sign_in_status(int *current_status) {
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

    sign_in_api(username, password, sign_in_callback, current_status);
}
