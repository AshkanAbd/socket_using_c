#include "interface/interface.h"
#include "Core/HtmlParser/html_parser.h"

void login_ok();

void static_file();

void login_invalid_action();

void login_not_found();

void html_test();

int main() {
//    login_ok();

//    static_file();

//    login_invalid_action();
//
//    login_not_found();

    html_test();
}

void html_test() {
    struct IncomingResponse *response = api_read("/digikala.html", NULL, 0);
    printf("%s\n", response_to_file_single_path(response, "output/digikala.html"));

    struct HtmlParser *html_parser = malloc(sizeof(struct HtmlParser));
    memset(html_parser, 0, sizeof(struct HtmlParser));

    init_html_parser(html_parser, response->data, response->data_size);
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

void login_ok() {
    struct IncomingResponse *response = api_read("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void static_file() {
    struct IncomingResponse *response = api_read("/gta.png", NULL, 0);
    printf("Status %d in static file\n", response->status);
    if (response->status == RESPONSE_NOT_FOUND) {
        printf("static file notfound");
        return;
    }
    printf("%s\n", response_to_file_single_path(response, "output/img/csgo.png"));
}

void login_invalid_action() {
    struct IncomingResponse *response = api_delete("/login", NULL, 0);

    printf("%s\n", response_to_str(response));
}

void login_not_found() {
    struct IncomingResponse *response = api_delete("/login1", NULL, 0);

    printf("%s\n", response_to_str(response));
}
