#include "interface.h"

int current_status = 0;

void print_error_repose(IncomingResponse *response) {
    char *msg = malloc(response->data_size + 1);
    memset(msg, 0, response->data_size + 1);
    memcpy(msg, response->data, response->data_size);
    printf("Error: %s\n", msg);
}

void change_life_cycle_status(int next_status) {
    current_status = next_status;
}

int get_life_cycle_status() {
    return current_status;
}