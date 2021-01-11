#include "interface.h"

void post_list_callback(IncomingResponse *response, void *ptr) {
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        change_life_cycle_status(STATUS_START);
        return;
    }
    int a = 0;
}

void post_list_status() {
    printf("Fetching posts from server, please wait...\n");

    post_list_api(post_list_callback, NULL);
}