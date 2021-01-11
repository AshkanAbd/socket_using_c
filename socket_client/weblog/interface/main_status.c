#include "interface.h"

void start_status() {
    int input = 0;

    do {
        printf("Select an action\n");
        printf("1) Sign in\n");
        printf("2) Sign up\n");
        input = getchar() - '0';
        while (getchar() != '\n');
    } while (input != 1 && input != 2);

    change_life_cycle_status(input);
}