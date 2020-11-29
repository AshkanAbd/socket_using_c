#include "interface.h"

struct IncomingResponse *request_builder() {
    int action;
    do {
        printf("Select action:\n");
        printf("1) Read\n");
        printf("2) Create\n");
        printf("3) Update\n");
        printf("4) Delete\n");
        action = getchar();
    } while (action < '1' || action > '4');
    action -= '0';
    getchar();

    printf("Enter route:\n");
    char *route = malloc(256);
    int route_size = 0;
    memset(route, 0, 256);
    char c;
    while ((c = getchar()) != '\n') {
        if (route_size >= 256) {
            break;
        }
        *(route + route_size++) = c;
    }

    printf("Enter params:\n");
    char *param = malloc(256);
    int param_size = 0;
    memset(param, 0, 256);
    while ((c = getchar()) != '\n') {
        if (param_size >= 256) {
            break;
        }
        *(param + param_size++) = c;
    }

    char *body = malloc(256);
    memset(body, 0, 256);
    int body_size = 0;
    if (action == REQUEST_CREATE || action == REQUEST_UPDATE) {
        printf("Enter body:\n");
        while ((c = getchar()) != '\n') {
            if (body_size >= 256) {
                break;
            }
            *(body + body_size++) = c;
        }
    }

    switch (action) {
        case REQUEST_READ:
            return api_read(route, param, param_size);
        case REQUEST_CREATE:
            return api_create(route, param, param_size, body, body_size);
        case REQUEST_UPDATE:
            return api_update(route, param, param_size, body, body_size);
        case REQUEST_DELETE:
            return api_delete(route, param, param_size);
    }
    return NULL;
}

void response_handler(struct IncomingResponse *response) {
    int output_type;
    do {
        printf("Print content to console or file?\n");
        printf("1) console\n");
        printf("2) file\n");
        output_type = getchar();
    } while (output_type != '1' && output_type != '2');
    getchar();

    char *filepath = malloc(1024);
    int filepath_size = 0;
    memset(filepath, 0, 1024);
    char c;
    if (output_type == '2') {
        printf("Enter filepath:\n");
        while ((c = getchar()) != '\n') {
            *(filepath + filepath_size++) = c;
        }
    }

    if (output_type == '1') {
        printf("%s\n", response_to_str(response));
    }
    if (output_type == '2') {
        printf("%s\n", response_to_file(response, filepath));
    }
}
