#include "interface.h"

void start_status(int *current_status) {
    int input = 0;

    do {
        printf("select action\n");
        printf("1) sign in\n");
        printf("2) sign up\n");
        input = getchar() - '0';
        while (getchar() != '\n');
    } while (input != 1 && input != 2);

    *current_status = input;
}