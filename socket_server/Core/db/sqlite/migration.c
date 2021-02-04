#include "migration.h"

int valid_users_table = 0;
char *users_table_sql = "CREATE TABLE users(id INTEGER not null constraint users_pk primary key autoincrement,username TEXT,password TEXT,created_at Datetime default current_timestamp,updated_at Datetime default current_timestamp)";
char *drop_users_sql = "DROP TABLE IF EXISTS users;";

int valid_posts_table = 0;
char *posts_table_sql = "CREATE TABLE posts(id INTEGER constraint posts_pk primary key autoincrement,title text not null,description text not null,user_id INTEGER references users on delete cascade,created_at datetime default current_timestamp,updated_at datetime default current_timestamp)";
char *drop_posts_sql = "DROP TABLE IF EXISTS posts;";

int valid_token_table = 0;
char *tokens_table_sql = "CREATE TABLE tokens(id integer constraint tokens_pk primary key autoincrement, token text not null,user_id INTEGER constraint tokens_users_id_fk references users on delete cascade)";
char *drop_tokens_sql = "DROP TABLE IF EXISTS tokens;";

/**
 * Prints database error on startup.
 * @param db
 */
void database_error(sqlite3 *db) {
    printf("Database error %s\n", sqlite3_errmsg(db));
    exit(1);
}

/**
 * Connects database with given filepath.
 * @param filename
 * @param db
 */
void connect_database(char *filename, sqlite3 **db) {
    if (sqlite3_open(filename, db) != SQLITE_OK) {
        database_error(*db);
    } else {
        printf("Database connection established.\n");
    }
}

int check_users_table(void *ptr, int row_count, char **data, char **columns) {
    if (strcmp(data[0], users_table_sql) == 0) {
        valid_users_table = 1;
    } else {
        valid_users_table = 0;
    }
    return 0;
}

int check_posts_table(void *ptr, int row_count, char **data, char **columns) {
    if (strcmp(data[0], posts_table_sql) == 0) {
        valid_posts_table = 1;
    } else {
        valid_posts_table = 0;
    }
    return 0;
}

int check_tokens_table(void *ptr, int row_count, char **data, char **columns) {
    if (strcmp(data[0], tokens_table_sql) == 0) {
        valid_token_table = 1;
    } else {
        valid_token_table = 0;
    }
    return 0;
}

void check_tables(sqlite3 *db) {
    char *msg = 0;
    if (sqlite3_exec(db, "SELECT sql FROM sqlite_master WHERE type = 'table' and name = 'users';",
                     check_users_table, db, &msg) != SQLITE_OK) {
        database_error(db);
    } else {
        printf("Checking users table...\n");
    }

    if (!valid_users_table) {
        printf("users table wasn't valid, creating a new one\n");
        if (sqlite3_exec(db, drop_users_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
        if (sqlite3_exec(db, users_table_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
    } else {
        printf("users table is valid.\n");
    }

    if (sqlite3_exec(db, "SELECT sql FROM sqlite_master WHERE type = 'table' and name = 'posts';",
                     check_posts_table, db, &msg) != SQLITE_OK) {
        database_error(db);
    } else {
        printf("Checking posts table...\n");
    }

    if (!valid_posts_table) {
        printf("posts table wasn't valid, creating a new one\n");
        if (sqlite3_exec(db, drop_posts_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
        if (sqlite3_exec(db, posts_table_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
    } else {
        printf("posts table is valid.\n");
    }

    if (sqlite3_exec(db, "SELECT sql FROM sqlite_master WHERE type = 'table' and name = 'tokens';",
                     check_tokens_table, db, &msg) != SQLITE_OK) {
        database_error(db);
    } else {
        printf("Checking tokens table...\n");
    }

    if (!valid_token_table) {
        printf("tokens table wasn't valid, creating a new one\n");
        if (sqlite3_exec(db, drop_tokens_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
        if (sqlite3_exec(db, tokens_table_sql, 0, 0, &msg) != SQLITE_OK) {
            database_error(db);
        }
    } else {
        printf("tokens table is valid.\n");
    }
}

void init_database(char *filename) {
    connect_database(filename, &db_connection);

    check_tables(db_connection);
}
