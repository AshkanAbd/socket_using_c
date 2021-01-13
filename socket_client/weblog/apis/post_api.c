#include "apis.h"

int server_port;
char *server_ip;

void post_list_api(void callback(IncomingResponse *, void *), void *ptr) {
    IncomingResponse *response = api_read("/post_list", NULL, 0, server_ip, server_port);

    callback(response, ptr);
}

void get_post_api(const char *id, void callback(IncomingResponse *, void *), void *ptr) {
    IncomingResponse *response = api_read("/get_post", (char *) id, (int) strlen(id), server_ip, server_port);

    callback(response, ptr);
}

void create_post_api(const char *token, const char *post_char, void callback(IncomingResponse *, void *), void *ptr) {
    IncomingResponse *response = api_create("/create_post", (char *) token, (int) strlen(token),
                                            (char *) post_char, strlen(post_char), server_ip, server_port);

    callback(response, ptr);
}
