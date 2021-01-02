#include "interface.h"

struct IncomingResponse *request_builder() {
    char *ip = malloc(1024);
    memset(ip, 0, 1024);
    printf("Enter ip:\n");
    scanf("%s", ip);

    int port = 0;
    printf("Enter port:\n");
    scanf("%d", &port);

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

    struct IncomingResponse *incoming_response = NULL;
    switch (action) {
        case REQUEST_READ:
            incoming_response = api_read(route, param, param_size, ip, port);
            set_port_and_ip(incoming_response, ip, port);
            break;
        case REQUEST_CREATE:
            incoming_response = api_create(route, param, param_size, body, body_size, ip, port);
            set_port_and_ip(incoming_response, ip, port);
            break;
        case REQUEST_UPDATE:
            incoming_response = api_update(route, param, param_size, body, body_size, ip, port);
            set_port_and_ip(incoming_response, ip, port);
            break;
        case REQUEST_DELETE:
            incoming_response = api_delete(route, param, param_size, ip, port);
            set_port_and_ip(incoming_response, ip, port);
            break;
    }
    return incoming_response;
}

void response_handler(struct IncomingResponse *response) {
    if (response == NULL) {
        return;
    }
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
        printf("%s\n", response_to_file_single_path(response, filepath));
        printf("Do you need HTML parser?(Y/n)\n");
        c = getchar();
        if (c == 'y' || c == 'Y') {
            struct HtmlParser *html_parser = malloc(sizeof(struct HtmlParser));
            memset(html_parser, 0, sizeof(struct HtmlParser));

            init_html_parser(html_parser, response->data, response->data_size, response->ip, response->port);
            free(response->data);
            free(response);
            while (has_more_img(html_parser)) {
                download_current_img(html_parser, "output/");
            }
            printf("Images downloaded\n");
            while (has_more_script(html_parser)) {
                download_current_script(html_parser, "output/");
            }
            printf("Scripts downloaded\n");
            while (has_more_css(html_parser)) {
                download_current_css(html_parser, "output/");
            }
            printf("Css downloaded\n");
            printf("Total downloaded files: %d\n", html_parser->total_downloads);
        }
    }
}
