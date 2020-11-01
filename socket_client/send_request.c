#include "Core/Socket/client.h"
#include "Core/Api/api.h"

void send_request(struct Client *client) {
    struct IncomingResponse *response = read_api(client, "/hello", NULL, 0);
}
