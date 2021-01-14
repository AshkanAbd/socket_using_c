#include "callbacks.h"

int find_user_by_username_callback(void *ptr, int row_count, char **data, char **columns) {
    User **user = (User **) ptr;
    *user = malloc(sizeof(User));
    memset(*user, 0, sizeof(User));

    init_user_full(*user, atoi(data[0]), data[1], data[2], data[3], data[4]);
    return 0;
}

int find_user_by_id_callback(void *ptr, int row_count, char **data, char **columns) {
    User **user = (User **) ptr;
    *user = malloc(sizeof(User));
    memset(*user, 0, sizeof(User));

    init_user_full(*user, atoi(data[0]), data[1], data[2], data[3], data[4]);
    return 0;
}
