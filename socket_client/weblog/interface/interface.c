#include "interface.h"

int current_status = 0;

void print_error_repose(IncomingResponse *response) {
    char *msg = malloc(response->data_size + 1);
    memset(msg, 0, response->data_size + 1);
    memcpy(msg, response->data, response->data_size);
    switch (response->status) {
        case RESPONSE_SERVER_ERROR:
            printf("Server internal Error: ");
            break;
        case RESPONSE_BAD_REQUEST:
            printf("Bad request Error: ");
            break;
        case RESPONSE_INVALID_ACTION:
            printf("Invalid action Error: ");
            break;
        case RESPONSE_NOT_FOUND:
            printf("Resource notfound Error: ");
            break;
        case RESPONSE_INVALID_SYNTAX:
            printf("Invalid request syntax Error: ");
            break;
        default:
            printf("Error: ");
            break;
    }
    printf("%s\n", msg);
    free(msg);
}

void change_life_cycle_status(int next_status) {
    current_status = next_status;
}

int get_life_cycle_status() {
    return current_status;
}

void print_post(IncomingResponse *response) {
    printf("\n######### NEW POST #########\n");
    for (size_t i = 0, j = 0; i < response->data_size; j++) {
        size_t data_size = i;
        size_t data_start = i;

        while (*((char *) response->data + data_size++) != 0x1E) {
            if (data_size >= response->data_size) {
                goto end;
            }
        }

        char *data = malloc(((data_size - data_start) * sizeof(char)));
        memset(data, 0, ((data_size - data_start) * sizeof(char)));
        memcpy(data, response->data + data_start, data_size - data_start - 1);

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

        printf("%s\n", data);

        free(data);

        i = data_size;
    }
    end:
    printf("########### END ###########\n\n");
}
