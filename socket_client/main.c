#include "interface/interface.h"
#include "weblog/life_cycle.h"

void login_ok();

void sign_up_op();

void static_file();

void login_invalid_action();

void login_not_found();

void html_test();

void get_posts() {
    struct IncomingResponse *response = api_read("/get_post", "3", 1, "127.0.0.1", 8080);

    printf("%s\n", response_to_str(response));
}

int main(int argc, char **argv) {
    start_life_cycle("127.0.0.1", 8080);
//    login_ok();
//    sign_up_op();
//    get_posts();
//    static_file();

//    login_invalid_action();

//    login_not_found();

//    html_test();

//    while (1) {
//        response_handler(request_builder());
//    }
}

//course.hws@gmail.com
void html_test() {
    struct IncomingResponse *response = api_read("/aparat.html", NULL, 0, "127.0.0.1", 8080);
    printf("%s\n", response_to_file_single_path(response, "output/aparat.html"));

    struct HtmlParser *html_parser = malloc(sizeof(struct HtmlParser));
    memset(html_parser, 0, sizeof(struct HtmlParser));

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

void login_ok() {
    const char *username = "username";
    const char *password = "password";
    char *params = malloc(strlen(username) + 1 + strlen(password) + 2);
    memset(params, 0, strlen(username) + 1 + strlen(password) + 2);
    memcpy(params, username, strlen(username));
    memcpy(params + strlen(username) + 1, password, strlen(password));
    *(params + strlen(username)) = 0x1E;
    *(params + strlen(username) + 1 + strlen(password)) = 0x1E;
    struct IncomingResponse *response = api_create("/sign_in", NULL, 0, params, (int) strlen(params), "127.0.0.1",
                                                   8080);

    printf("%s\n", response_to_str(response));
}

void sign_up_op() {
    const char *username = "username";
    const char *password = "password";
    char *params = malloc(strlen(username) + 1 + strlen(password) + 2);
    memset(params, 0, strlen(username) + 1 + strlen(password) + 2);
    memcpy(params, username, strlen(username));
    memcpy(params + strlen(username) + 1, password, strlen(password));
    *(params + strlen(username)) = 0x1E;
    *(params + strlen(username) + 1 + strlen(password)) = 0x1E;
    struct IncomingResponse *response = api_create("/sign_up", NULL, 0, params, (int) strlen(params), "127.0.0.1",
                                                   8080);

    printf("%s\n", response_to_str(response));
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

void login_invalid_action() {
    struct IncomingResponse *response = api_delete("/login", NULL, 0, "127.0.0.1", 8080);

    printf("%s\n", response_to_str(response));
}

void login_not_found() {
    struct IncomingResponse *response = api_delete("/login1", NULL, 0, "127.0.0.1", 8080);

    printf("%s\n", response_to_str(response));
}
