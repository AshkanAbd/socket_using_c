#include "interface.h"

char *token;

void create_post_callback(IncomingResponse *response, void *ptr) {
    change_life_cycle_status(STATUS_POST_ACTION);
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        return;
    }

    print_post(response);
}

void create_post_status() {
    printf("Fill information to create a post\n");

    char c;
    int index = 0;

    char *title = malloc(1024);
    memset(title, 0, 1024);
    printf("Enter post title: ");

    while ((c = getchar()) != '\n') {
        *(title + index++) = c;
    }

    char *description = malloc(1024);
    memset(description, 0, 1024);
    printf("Enter post description: ");
    index = 0;

    while ((c = getchar()) != '\n') {
        *(description + index++) = c;
    }

    char *params = malloc(strlen(title) + 1 + strlen(description) + 2);
    memset(params, 0, strlen(title) + 1 + strlen(description) + 2);
    memcpy(params, title, strlen(title));
    memcpy(params + strlen(title) + 1, description, strlen(description));
    *(params + strlen(title)) = 0x1E;
    *(params + strlen(title) + 1 + strlen(description)) = 0x1E;

    printf("Creating a post in server, please wait...\n");
    create_post_api(token, params, create_post_callback, NULL);

    free(title);
    free(description);
    free(params);
}