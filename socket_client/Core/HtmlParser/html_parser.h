#ifndef SOCKET_CLIENT_HTML_PARSER_H
#define SOCKET_CLIENT_HTML_PARSER_H

#include "../Api/api.h"

struct HtmlParser {
    char *content;
    char *ip;
    int port;
    int total_downloads;
    unsigned long long int content_size;
    unsigned long long int img_position;
    unsigned long long int script_position;
    unsigned long long int css_position;
    int result_flag;
    const char *css_rel;
    const char *css_tag;
    const char *img_tag;
    const char *script_tag;
};

void init_html_parser(struct HtmlParser *html_parser, char *data, unsigned long long int data_size,
                      char *ip, int port);

int has_more_img(struct HtmlParser *html_parser);

int download_current_img(struct HtmlParser *html_parser, const char *prefix);

int has_more_script(struct HtmlParser *html_parser);

int download_current_script(struct HtmlParser *html_parser, const char *prefix);

int has_more_css(struct HtmlParser *html_parser);

int download_current_css(struct HtmlParser *html_parser, const char *prefix);

int download_html_object(struct HtmlParser *html_parser, const char *prefix, unsigned long long int start_index,
                         unsigned long long int end_index);

#endif //SOCKET_CLIENT_HTML_PARSER_H
