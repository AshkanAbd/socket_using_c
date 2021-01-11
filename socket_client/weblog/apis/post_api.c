#include "apis.h"

int server_port;
char *server_ip;

void post_list_api(void callback(IncomingResponse *, void *), void *ptr) {
    IncomingResponse *response = api_read("/post", NULL, 0, server_ip, server_port);

    callback(response, ptr);
}
