#include "interface.h"

void get_one_post_callback(IncomingResponse *response, void *ptr) {
    change_life_cycle_status(STATUS_POST_ACTION);
    if (response->status != RESPONSE_OK) {
        print_error_repose(response);
        return;
    }

    for (size_t i = 0, j = 0; i < response->data_size; j++) {
        switch (j % 6) {
            case 0:
                printf("Post id: ");
                break;
            case 1:
                printf("Title: ");
                break;
            case 2:
                printf("Description: ");
                break;
            case 3:
                printf("Created at: ");
                break;
            case 4:
                printf("User id: ");
                break;
            case 5:
                printf("Username: ");
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

    printf("Fetching posts from server, please wait...\n");

    get_post_api(id_char, get_one_post_callback, NULL);
    free(id_char);
}