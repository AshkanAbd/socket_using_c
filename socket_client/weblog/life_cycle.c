#include "life_cycle.h"

int current_status = 0;

int server_port;
char *server_ip;
char *token;

void start_life_cycle(const char *ip, int port) {

    server_port = port;
    server_ip = malloc(strlen(ip) + 1);
    memset(server_ip, 0, strlen(ip) + 1);
    memcpy(server_ip, ip, strlen(ip));

    while (1) {
        if (current_status == STATUS_START) {
            start_status(&current_status);
        }
        if (current_status == STATUS_SIGN_IN) {
            sign_in_status(&current_status);
        }
    }
}
