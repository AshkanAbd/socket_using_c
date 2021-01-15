#include "interface.h"

char *token;

void delete_post_callback(IncomingResponse *response, void *ptr) {
    change_life_cycle_status(STATUS_POST_ACTION);
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        return;
    }
    char *msg = malloc(response->data_size + 1);
    memset(msg, 0, response->data_size + 1);
    memcpy(msg, response->data, response->data_size);

    printf("%s\n", msg);
    free(msg);
}

void delete_post_status() {
    printf("Enter post id: ");
    char *id_char = malloc(1024);
    memset(id_char, 0, 1024);

    char c;
    int index = 0;
    while ((c = getchar()) != '\n') {
        *(id_char + index++) = c;
    }

    printf("deleting post in server, please wait...\n");
    delete_post_api(id_char, token, delete_post_callback, NULL);

    free(id_char);
}
