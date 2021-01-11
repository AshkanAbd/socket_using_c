#include "interface.h"

void post_list_callback(IncomingResponse *response, void *ptr) {
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        change_life_cycle_status(STATUS_START);
        return;
    }

    char posts_count_char[sizeof(int)];
    memmove(posts_count_char, response->data, sizeof(int));

    int posts_count = atoi(posts_count_char);
    printf("%d posts retrieved from server\n", posts_count);
    for (size_t i = sizeof(int) + 1, j = 0; i < response->data_size; j++) {
        switch (j % 3) {
            case 0:
                printf("######### NEW POST #########\n");
                printf("Id: ");
                break;
            case 1:
                printf("Title: ");
                break;
            case 2:
                printf("Created at: ");
                break;
        }

        size_t data_size = i;
        size_t data_start = i;

        while (*((char *) response->data + data_size++) != 0x1E);

        char *data = malloc(((data_size - data_start) * sizeof(char)));
        memset(data, 0, ((data_size - data_start) * sizeof(char)));
        memcpy(data, response->data + data_start, data_size - data_start - 1);

        printf("%s\n", data);

        free(data);

        i = data_size;
    }
    printf("######### END #########\n");
    change_life_cycle_status(STATUS_POST_ACTION);
}

void post_list_status() {
    printf("Fetching posts from server, please wait...\n");

    post_list_api(post_list_callback, NULL);
}