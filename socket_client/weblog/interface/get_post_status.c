#include "interface.h"

void get_one_post_callback(IncomingResponse *response, void *ptr) {
    change_life_cycle_status(STATUS_POST_ACTION);
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        return;
    }

    print_post(response);
}

void get_post_status() {
    printf("Enter post id: ");
    char *id_char = malloc(1024);
    memset(id_char, 0, 1024);

    char c;
    int index = 0;
    while ((c = getchar()) != '\n') {
        *(id_char + index++) = c;
    }

    printf("Fetching post with given id from server, please wait...\n");

    get_post_api(id_char, get_one_post_callback, NULL);
    free(id_char);
}