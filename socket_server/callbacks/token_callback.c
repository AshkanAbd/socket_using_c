#include "callbacks.h"

int get_token_callback(void *ptr, int row_count, char **data, char **columns) {
    Token **token = (Token **) ptr;

    *token = malloc(sizeof(Token));
    memset(*token, 0, sizeof(Token));

    init_token(*token, data[1], atoi(data[2]));

    return 0;
}
