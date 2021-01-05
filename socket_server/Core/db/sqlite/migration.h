#ifndef SOCKET_SERVER_MIGRATION_H
#define SOCKET_SERVER_MIGRATION_H

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_database(char *filename);

sqlite3 *db_connection;

#endif //SOCKET_SERVER_MIGRATION_H
