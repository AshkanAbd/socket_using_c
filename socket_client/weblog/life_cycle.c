#include "life_cycle.h"

int server_port;
char *server_ip;
char *token;

void start_life_cycle(const char *ip, int port) {

    server_port = port;
    server_ip = malloc(strlen(ip) + 1);
    memset(server_ip, 0, strlen(ip) + 1);
    memcpy(server_ip, ip, strlen(ip));

    while (1) {
        if (get_life_cycle_status() == STATUS_START) {
            start_status();
        }
        if (get_life_cycle_status() == STATUS_SIGN_IN) {
            sign_in_status();
        }
        if (get_life_cycle_status() == STATUS_SIGN_UP) {
            sign_up_status();
        }
        if (get_life_cycle_status() == STATUS_POST_ACTION) {
            post_action_status();
        }
        if (get_life_cycle_status() == STATUS_POST_LIST) {
            post_list_status();
        }
        if (get_life_cycle_status() == STATUS_GET_ONE_POST) {
            get_post_status();
        }
        if (get_life_cycle_status() == STATUS_CREATE_POST) {
            create_post_status();
        }
        if (get_life_cycle_status() == STATUS_UPDATE_POST) {
            update_post_status();
        }
    }
}
