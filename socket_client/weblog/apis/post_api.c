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
