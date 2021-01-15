#include "apis.h"

int server_port;
char *server_ip;

void post_list_api(void callback(IncomingResponse *, void *), void *ptr) {
    IncomingResponse *response = api_read("/post_list", NULL, 0, server_ip, server_port);

    callback(response, ptr);
}

void get_post_api(const char *id, void callback(IncomingResponse *, void *), void *ptr) {
    char *param = malloc(strlen(id) + 2);
    memset(param, 0, strlen(id) + 2);

    memcpy(param, id, strlen(id));
    *(param + strlen(id)) = 0x1E;

    IncomingResponse *response = api_read("/get_post", param, (int) strlen(param), server_ip, server_port);

    callback(response, ptr);
}

void create_post_api(const char *token, const char *post_char, void callback(IncomingResponse *, void *), void *ptr) {
    char *param = malloc(strlen(token) + 2);
    memset(param, 0, strlen(token) + 2);

    memcpy(param, token, strlen(token));
    *(param + strlen(token)) = 0x1E;

    IncomingResponse *response = api_create("/create_post", param, strlen(param),
                                            (char *) post_char, strlen(post_char), server_ip, server_port);

    callback(response, ptr);
}

void update_post_api(const char *id, const char *token, const char *post_char,
                     void callback(IncomingResponse *, void *), void *ptr) {
    char *param = malloc(strlen(token) + 1 + strlen(id) + 2);
    memset(param, 0, strlen(token) + 1 + strlen(id) + 2);

    memcpy(param, token, strlen(token));
    *(param + strlen(token)) = 0x1E;

    memcpy(param + strlen(token) + 1, id, strlen(id));
    *(param + strlen(token) + 1 + strlen(id)) = 0x1E;

    IncomingResponse *response = api_update("/update_post", param, strlen(param),
                                            (char *) post_char, strlen(post_char), server_ip, server_port);

    callback(response, ptr);
}

void delete_post_api(const char *id, const char *token, void callback(IncomingResponse *, void *), void *ptr) {
    char *param = malloc(strlen(token) + 1 + strlen(id) + 2);
    memset(param, 0, strlen(token) + 1 + strlen(id) + 2);

    memcpy(param, token, strlen(token));
    *(param + strlen(token)) = 0x1E;

    memcpy(param + strlen(token) + 1, id, strlen(id));
    *(param + strlen(token) + 1 + strlen(id)) = 0x1E;

    IncomingResponse *response = api_delete("/delete_post", param, strlen(param), server_ip, server_port);

    callback(response, ptr);
}
