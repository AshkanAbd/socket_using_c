/**
 * Queries Callback header file, All queries callback functions should define here.
 */
#ifndef SOCKET_SERVER_CALLBACKS_H
#define SOCKET_SERVER_CALLBACKS_H

#include "../models/models.h"

int find_user_by_username_callback(void *ptr, int row_count, char **data, char **columns);

int find_user_by_id_callback(void *ptr, int row_count, char **data, char **columns);

int posts_count_callback(void *ptr, int row_count, char **data, char **columns);

int get_posts_callback(void *ptr, int row_count, char **data, char **columns);

int find_post_by_id_callback(void *ptr, int row_count, char **data, char **columns);

int get_new_post_callback(void *ptr, int row_count, char **data, char **columns);

int get_token_callback(void *ptr, int row_count, char **data, char **columns);

#endif //SOCKET_SERVER_CALLBACKS_H
