#ifndef SOCKET_CLIENT_HTML_PARSER_H
#define SOCKET_CLIENT_HTML_PARSER_H

#include "../Api/api.h"

struct HtmlParser {
    char *content;
    unsigned long long int content_size;
    unsigned long long int img_position;
    unsigned long long int script_position;
    unsigned long long int css_position;
};

void init_html_parser(struct HtmlParser *htmlParser, char *data, unsigned long long int data_size);

int has_more_img(struct HtmlParser *htmlParser);

int download_current_img(struct HtmlParser *htmlParser);

int has_more_script(struct HtmlParser *htmlParser);

int download_current_script(struct HtmlParser *htmlParser);

int has_more_css(struct HtmlParser *htmlParser);

int download_current_css(struct HtmlParser *htmlParser);

#endif //SOCKET_CLIENT_HTML_PARSER_H
