#include "interface.h"

void post_action_status() {
    int input = 0;

    do {
        printf("Select an action\n");
        printf("1) Get post list\n");
        printf("2) Get post\n");
        printf("3) Create post\n");
        printf("4) Update post\n");
        printf("5) Delete post\n");
        input = getchar() - '0';
        while (getchar() != '\n');
    } while (input < 1 || input > 6);

    switch (input) {
        case 1:
            change_life_cycle_status(STATUS_POST_LIST);
            break;
        case 2:
            change_life_cycle_status(STATUS_GET_ONE_POST);
            break;
        case 3:
            change_life_cycle_status(STATUS_CREATE_POST);
            break;
        case 4:
            change_life_cycle_status(STATUS_UPDATE_POST);
            break;
        case 5:
            change_life_cycle_status(STATUS_DELETE_POST);
            break;
        default:
            change_life_cycle_status(STATUS_POST_ACTION);
            break;
    }
}