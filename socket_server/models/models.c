#include "models.h"

int search_query(const char *table, const char *column, const char *value, void *ptr,
                 int (*callback)(void *, int, char **, char **), char **msg) {
    char *select_sql_part = "SELECT * FROM ";

    size_t from_sql_part_size = strlen(select_sql_part) + strlen(table) + 1;
    char *from_sql_part = malloc(from_sql_part_size);
    memset(from_sql_part, 0, from_sql_part_size);

    memcpy(from_sql_part, select_sql_part, strlen(select_sql_part));
    memcpy(from_sql_part + strlen(select_sql_part), table, strlen(table));
    *(from_sql_part + strlen(select_sql_part) + strlen(table)) = ' ';

    char *where_word = "where ";
    size_t where_sql_part_size = from_sql_part_size + strlen(where_word) + strlen(column) + 1;
    char *where_sql_part = malloc(where_sql_part_size);
    memset(where_sql_part, 0, from_sql_part_size);

    memcpy(where_sql_part, from_sql_part, from_sql_part_size);
    memcpy(where_sql_part + from_sql_part_size, where_word, strlen(where_word));
    memcpy(where_sql_part + from_sql_part_size + strlen(where_word), column, strlen(column));
    *(where_sql_part + from_sql_part_size + strlen(where_word) + strlen(column)) = ' ';


    size_t custom_search_sql_size = where_sql_part_size + 4 + strlen(value) + 2;
    char *custom_search_sql = malloc(custom_search_sql_size);
    memset(custom_search_sql, 0, custom_search_sql_size);

    memcpy(custom_search_sql, where_sql_part, where_sql_part_size);

    *(custom_search_sql + where_sql_part_size) = ' ';
    *(custom_search_sql + where_sql_part_size + 1) = '=';
    *(custom_search_sql + where_sql_part_size + 2) = ' ';
    *(custom_search_sql + where_sql_part_size + 3) = '\'';
    memcpy(custom_search_sql + where_sql_part_size + 4, value, strlen(value));
    *(custom_search_sql + where_sql_part_size + 4 + strlen(value)) = '\'';

    int query_result = sqlite3_exec(db_connection, custom_search_sql, callback, ptr, msg);

    free(from_sql_part);
    free(where_sql_part);
    free(custom_search_sql);

    return query_result;
}