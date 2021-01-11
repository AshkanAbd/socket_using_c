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