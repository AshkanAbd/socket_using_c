/**
 * The file that defines query functions.
 * All user-defined models should have a unique macro in this file.
 * For all user-defined models you should update functions in this file.
 */
#ifndef SOCKET_SERVER_MODELS_H
#define SOCKET_SERVER_MODELS_H

#include "post.h"
#include "token.h"
#include "user.h"

#define POST_TYPE   1
#define TOKEN_TYPE  2
#define USER_TYPE   3

/**
 * Returns table name by given macro.
 * Update it if you add a new model.
 * @param type
 * @param msg
 * @return
 */
const char *get_table(int type, char **msg);

/**
 * Returns table columns by given macro.
 * Update it if you add a new model.
 * @param type
 * @param msg
 * @return
 */
const char *get_columns(int type, char **msg);

/**
 * Returns table values template by given macro.
 * Update it if you add a new model.
 * @param type
 * @param msg
 * @return
 */
const char *get_value_template(int type, char **msg);

/**
 * Executes a search query by given macro.
 * Update it if you add a new model.
 * @param type
 * @param column
 * @param value
 * @param ptr
 * @param callback
 * @param msg
 * @return
 */
int search_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

/**
 * Executes an insert query by given macro.
 * Update it if you add a new model.
 * @param type
 * @param obj
 * @param ptr
 * @param callback
 * @param msg
 * @return
 */
int insert_query(int type, const void *obj, void *ptr, int (*callback)(void *, int, char **, char **), char **msg);

/**
 * Executes an update query by given macro.
 * Update it if you add a new model.
 * @param type
 * @param column
 * @param value
 * @param obj
 * @param ptr
 * @param callback
 * @param msg
 * @return
 */
int update_query(int type, const char *column, const char *value, const void *obj, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);
/**
 * Executes a delete query by given macro.
 * Update it if you add a new model.
 * @param type
 * @param column
 * @param value
 * @param ptr
 * @param callback
 * @param msg
 * @return
 */
int delete_query(int type, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg);

#endif //SOCKET_SERVER_MODELS_H
