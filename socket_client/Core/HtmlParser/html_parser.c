#include "html_parser.h"

void init_html_parser(struct HtmlParser *html_parser, char *data, unsigned long long int data_size,
                      char *ip, int port) {
    html_parser->content_size = data_size;

    html_parser->port = port;

    html_parser->ip = malloc(strlen(ip) + 1);
    memset(html_parser->ip, 0, strlen(ip) + 1);
    memcpy(html_parser->ip, ip, strlen(ip));

    html_parser->content = malloc(html_parser->content_size);
    memset(html_parser->content, 0, html_parser->content_size);
    memcpy(html_parser->content, data, html_parser->content_size);

    html_parser->img_position = 0;
    html_parser->script_position = 0;
    html_parser->css_position = 0;
    html_parser->total_downloads = 0;

    html_parser->css_rel = "rel=\"stylesheet\"";
    html_parser->css_tag = "<link ";
    html_parser->img_tag = "<img ";
    html_parser->script_tag = "<script ";
}

int is_img_tag(struct HtmlParser *html_parser, unsigned long long int index) {
    if (index + 5 >= html_parser->content_size) {
        return 0;
    }
    char *temp = malloc(6);
    memset(temp, 0, 6);
    memcpy(temp, html_parser->content + index, 5);

    html_parser->result_flag = strcmp(html_parser->img_tag, temp) == 0;
    free(temp);
    return html_parser->result_flag;
}

int is_script_tag(struct HtmlParser *html_parser, unsigned long long int index) {
    if (index + 8 >= html_parser->content_size) {
        return 0;
    }
    char *temp = malloc(9);
    memset(temp, 0, 9);
    memcpy(temp, html_parser->content + index, 8);

    html_parser->result_flag = strcmp(html_parser->script_tag, temp) == 0;
    free(temp);
    return html_parser->result_flag;
}

int is_css_tag(struct HtmlParser *html_parser, unsigned long long int index) {
    if (index + 6 >= html_parser->content_size) {
        return 0;
    }
    char *temp = malloc(7);
    memset(temp, 0, 7);
    memcpy(temp, html_parser->content + index, 6);

    if (strcmp(html_parser->css_tag, temp) != 0) {
        return 0;
    }
    free(temp);

    register unsigned long long int i = index;
    unsigned long long int j, k;

    int css_rel_check;
    for (; i < html_parser->content_size; i++) {
        if (*(html_parser->content + i) == '>') {
            return 0;
        }
        css_rel_check = 1;
        for (j = i, k = 0; k < strlen(html_parser->css_rel); j++, k++) {
            if (*(html_parser->content + j) != *(html_parser->css_rel + k)) {
                css_rel_check = 0;
                break;
            }
        }
        if (css_rel_check) {
            return 1;
        }
    }
    return 0;
}

int has_more_img(struct HtmlParser *html_parser) {
    register unsigned long long int i;
    for (i = html_parser->img_position + 1; i < html_parser->content_size; ++i) {
        if (*(html_parser->content + i) == '<' && is_img_tag(html_parser, i)) {
            html_parser->img_position = i;
            return 1;
        }
    }
    return 0;
}

int has_more_script(struct HtmlParser *html_parser) {
    register unsigned long long int i;
    for (i = html_parser->script_position + 1; i < html_parser->content_size; ++i) {
        if (*(html_parser->content + i) == '<' && is_script_tag(html_parser, i)) {
            html_parser->script_position = i;
            return 1;
        }
    }
    return 0;
}

int has_more_css(struct HtmlParser *html_parser) {
    register unsigned long long int i;
    for (i = html_parser->css_position + 1; i < html_parser->content_size; ++i) {
        if (*(html_parser->content + i) == '<' && is_css_tag(html_parser, i)) {
            html_parser->css_position = i;
            return 1;
        }
    }
    return 0;
}

int download_current_img(struct HtmlParser *html_parser, const char *prefix) {
    register unsigned long long int i = html_parser->img_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < html_parser->content_size - 4; i++) {
        if (*(html_parser->content + i) == '>' || *(html_parser->content + i) == ':') {
            return 0;
        }
        if (
                *(html_parser->content + i + 0) == ' ' &&
                *(html_parser->content + i + 1) == 's' &&
                *(html_parser->content + i + 2) == 'r' &&
                *(html_parser->content + i + 3) == 'c'
                ) {
            src_check = 1;
        }
        if (*(html_parser->content + i) == '\"' && src_check && start_index != (unsigned long long) -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(html_parser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }
    return download_html_object(html_parser, prefix, start_index, end_index);
}

int download_current_script(struct HtmlParser *html_parser, const char *prefix) {
    register unsigned long long int i = html_parser->script_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < html_parser->content_size - 4; i++) {
        if (*(html_parser->content + i) == '>') {
            return 0;
        }
        if (*(html_parser->content + i + 0) == 's' &&
            *(html_parser->content + i + 1) == 'r' &&
            *(html_parser->content + i + 2) == 'c') {
            src_check = 1;
        }
        if (*(html_parser->content + i) == '\"' && src_check && start_index != (unsigned long long) -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(html_parser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }

    return download_html_object(html_parser, prefix, start_index, end_index);
}

int download_current_css(struct HtmlParser *html_parser, const char *prefix) {
    register unsigned long long int i = html_parser->css_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < html_parser->content_size - 4; i++) {
        if (*(html_parser->content + i) == '>') {
            return 0;
        }
        if (*(html_parser->content + i + 0) == 'h' &&
            *(html_parser->content + i + 1) == 'r' &&
            *(html_parser->content + i + 2) == 'e' &&
            *(html_parser->content + i + 3) == 'f') {
            src_check = 1;
        }
        if (*(html_parser->content + i) == '\"' && src_check && start_index != (unsigned long long) -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(html_parser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }

    return download_html_object(html_parser, prefix, start_index, end_index);
}

int download_html_object(struct HtmlParser *html_parser, const char *prefix, unsigned long long int start_index,
                         unsigned long long int end_index) {
    char *absolute_url = malloc(end_index - start_index + 2);
    memset(absolute_url, 0, end_index - start_index + 2);
    *(absolute_url) = '/';
    memcpy(absolute_url + 1, html_parser->content + start_index, end_index - start_index);

    char *url = malloc(strlen(prefix) + end_index - start_index + 1);
    memset(url, 0, strlen(prefix) + end_index - start_index + 1);
    memcpy(url, prefix, strlen(prefix));
    memcpy(url + strlen(prefix), html_parser->content + start_index, end_index - start_index);

    struct IncomingResponse *response = api_read(absolute_url, NULL, 0, html_parser->ip, html_parser->port);
    if (response == NULL) {
        free(url);
        free(absolute_url);
        return 0;
    }
    if (response->status == RESPONSE_NOT_FOUND) {
        return 0;
    }
    char *download_path = response_to_file_single_path(response, url);
    printf("%s\n", download_path);

    free(response->data);
    free(response);
    free(url);
    free(absolute_url);
    free(download_path);

    html_parser->total_downloads++;
    return 1;
}
