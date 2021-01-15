#include "interface/interface.h"
#include "weblog/life_cycle.h"

int port = 8080;
char *ip = "127.0.0.1";

void check_args(int argc, char **argv);

void static_file();

void html_test();

int main(int argc, char **argv) {
    check_args(argc, argv);

    printf("Server IP: %s\nServer port: %d\n", ip, port);

    start_life_cycle(ip, port);

//    static_file();

//    html_test();

//    while (1) {
//        response_handler(request_builder());
//    }
}

//course.hws@gmail.com
void html_test() {
    struct IncomingResponse *response = api_read("/aparat.html", NULL, 0, "127.0.0.1", 8080);
    printf("%s\n", response_to_file_single_path(response, "output/aparat.html"));

    HtmlParser *html_parser = malloc(sizeof(HtmlParser));
    memset(html_parser, 0, sizeof(HtmlParser));

    init_html_parser(html_parser, response->data, response->data_size, "127.0.0.1", 8080);
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

void static_file() {
    struct IncomingResponse *response = api_read("/gta.png", NULL, 0, "127.0.0.1", 8080);
    printf("Status %d in static file\n", response->status);
    if (response->status == RESPONSE_NOT_FOUND) {
        printf("static file notfound");
        return;
    }
    printf("%s\n", response_to_file_single_path(response, "output/img/csgo.png"));
    free(response->data);
    free(response);
}

void check_args(int argc, char **argv) {
    if (argc > 1 && (strcmp(*(argv + 1), "--help") == 0 || strcmp(*(argv + 1), "-h") == 0)) {
        printf("socket_client.exe [ip] [port] [packet_size]");
        exit(1);
    }

    if (argc >= 2) {
        ip = *(argv + 1);
    }

    if (argc >= 3) {
        port = atoi(*(argv + 2));
    }

    if (argc >= 4) {
        change_max(atoi(*(argv + 3)));
    }
}