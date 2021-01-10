#include "interface.h"

char *token;

void sign_up_callback(IncomingResponse *response, void *ptr) {
    int *current_status = (int *) ptr;
    if (response->status == RESPONSE_OK) {
        printf("Sign up successful\n");
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

void sign_up_status(int *current_status) {
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
    sign_up_api(username, password, sign_up_callback, current_status);
}

