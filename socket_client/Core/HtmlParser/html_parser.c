#include "html_parser.h"

void init_html_parser(struct HtmlParser *htmlParser, char *data, unsigned long long int data_size) {
    htmlParser->content_size = data_size;
    htmlParser->content = malloc(htmlParser->content_size);

    memset(htmlParser->content, 0, htmlParser->content_size);

    memcpy(htmlParser->content, data, htmlParser->content_size);

    htmlParser->img_position = 0;
    htmlParser->script_position = 0;
    htmlParser->css_position = 0;
    htmlParser->total_downloads = 0;
}

int is_img_tag(struct HtmlParser *htmlParser, unsigned long long int index) {
    if (index + 5 >= htmlParser->content_size) {
        return 0;
    }
    char *temp = malloc(6);
    memset(temp, 0, 6);
    memcpy(temp, htmlParser->content + index, 5);

    return strcmp("<img ", temp) == 0;
}

int is_script_tag(struct HtmlParser *htmlParser, unsigned long long int index) {
    if (index + 8 >= htmlParser->content_size) {
        return 0;
    }
    char *temp = malloc(9);
    memset(temp, 0, 9);
    memcpy(temp, htmlParser->content + index, 8);

    return strcmp("<script ", temp) == 0;
}

int is_css_tag(struct HtmlParser *htmlParser, unsigned long long int index) {
    if (index + 6 >= htmlParser->content_size) {
        return 0;
    }
    char *temp = malloc(7);
    memset(temp, 0, 7);
    memcpy(temp, htmlParser->content + index, 6);

    if (strcmp("<link ", temp) != 0) {
        return 0;
    }

    register unsigned long long int i = index;
    unsigned long long int j, k;

    int css_rel_check;
    char *css_rel = "rel=\"stylesheet\"";

    for (; i < htmlParser->content_size; i++) {
        if (*(htmlParser->content + i) == '>') {
            return 0;
        }
        css_rel_check = 1;
        for (j = i, k = 0; k < strlen(css_rel); j++, k++) {
            if (*(htmlParser->content + j) != *(css_rel + k)) {
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

int has_more_img(struct HtmlParser *htmlParser) {
    register unsigned long long int i;
    for (i = htmlParser->img_position + 1; i < htmlParser->content_size; ++i) {
        if (*(htmlParser->content + i) == '<' && is_img_tag(htmlParser, i)) {
            htmlParser->img_position = i;
            return 1;
        }
    }
    return 0;
}

int download_current_img(struct HtmlParser *htmlParser, const char *prefix) {
    register unsigned long long int i = htmlParser->img_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < htmlParser->content_size - 4; i++) {
        if (*(htmlParser->content + i) == '>') {
            return 0;
        }
        if (
                *(htmlParser->content + i + -1) == ' ' &&
                *(htmlParser->content + i + 0) == 's' &&
                *(htmlParser->content + i + 1) == 'r' &&
                *(htmlParser->content + i + 2) == 'c'
                ) {
            src_check = 1;
        }
        if (*(htmlParser->content + i) == '\"' && src_check && start_index != -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(htmlParser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }

    char *absolute_url = malloc(end_index - start_index + 2);
    memset(absolute_url, 0, end_index - start_index + 2);
    *(absolute_url) = '/';
    memcpy(absolute_url + 1, htmlParser->content + start_index, end_index - start_index);

    char *url = malloc(strlen(prefix) + end_index - start_index + 1);
    memset(url, 0, strlen(prefix) + end_index - start_index + 1);
    memcpy(url, prefix, strlen(prefix));
    memcpy(url + strlen(prefix), htmlParser->content + start_index, end_index - start_index);

    struct IncomingResponse *response = api_read(absolute_url, NULL, 0);
    if (response->status == RESPONSE_NOT_FOUND) {
        return 0;
    }
    printf("%s\n", response_to_file_single_path(response, url));
    htmlParser->total_downloads++;
    return 1;
}

int has_more_script(struct HtmlParser *htmlParser) {
    register unsigned long long int i;
    for (i = htmlParser->script_position + 1; i < htmlParser->content_size; ++i) {
        if (*(htmlParser->content + i) == '<' && is_script_tag(htmlParser, i)) {
            htmlParser->script_position = i;
            return 1;
        }
    }
    return 0;
}

int download_current_script(struct HtmlParser *htmlParser, const char *prefix) {
    register unsigned long long int i = htmlParser->script_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < htmlParser->content_size - 4; i++) {
        if (*(htmlParser->content + i) == '>') {
            return 0;
        }
        if (*(htmlParser->content + i + 0) == 's' &&
            *(htmlParser->content + i + 1) == 'r' &&
            *(htmlParser->content + i + 2) == 'c') {
            src_check = 1;
        }
        if (*(htmlParser->content + i) == '\"' && src_check && start_index != -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(htmlParser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }

    char *absolute_url = malloc(end_index - start_index + 2);
    memset(absolute_url, 0, end_index - start_index + 2);
    *(absolute_url) = '/';
    memcpy(absolute_url + 1, htmlParser->content + start_index, end_index - start_index);

    char *url = malloc(strlen(prefix) + end_index - start_index + 1);
    memset(url, 0, strlen(prefix) + end_index - start_index + 1);
    memcpy(url, prefix, strlen(prefix));
    memcpy(url + strlen(prefix), htmlParser->content + start_index, end_index - start_index);

    struct IncomingResponse *response = api_read(absolute_url, NULL, 0);
    if (response->status == RESPONSE_NOT_FOUND) {
        return 0;
    }
    printf("%s\n", response_to_file_single_path(response, url));
    htmlParser->total_downloads++;
    return 1;
}

int has_more_css(struct HtmlParser *htmlParser) {
    register unsigned long long int i;
    for (i = htmlParser->css_position + 1; i < htmlParser->content_size; ++i) {
        if (*(htmlParser->content + i) == '<' && is_css_tag(htmlParser, i)) {
            htmlParser->css_position = i;
            return 1;
        }
    }
    return 0;
}

int download_current_css(struct HtmlParser *htmlParser, const char *prefix) {
    register unsigned long long int i = htmlParser->css_position;
    unsigned long long int start_index = -1, end_index = -1;
    int src_check = 0;
    int done_check = 0;
    for (; i < htmlParser->content_size - 4; i++) {
        if (*(htmlParser->content + i) == '>') {
            return 0;
        }
        if (*(htmlParser->content + i + 0) == 'h' &&
            *(htmlParser->content + i + 1) == 'r' &&
            *(htmlParser->content + i + 2) == 'e' &&
            *(htmlParser->content + i + 3) == 'f') {
            src_check = 1;
        }
        if (*(htmlParser->content + i) == '\"' && src_check && start_index != -1) {
            end_index = i;
            done_check = 1;
            break;
        }
        if (*(htmlParser->content + i) == '\"' && src_check) {
            start_index = i + 1;
        }
    }
    if (!done_check) {
        return 0;
    }

    char *absolute_url = malloc(end_index - start_index + 2);
    memset(absolute_url, 0, end_index - start_index + 2);
    *(absolute_url) = '/';
    memcpy(absolute_url + 1, htmlParser->content + start_index, end_index - start_index);

    char *url = malloc(strlen(prefix) + end_index - start_index + 1);
    memset(url, 0, strlen(prefix) + end_index - start_index + 1);
    memcpy(url, prefix, strlen(prefix));
    memcpy(url + strlen(prefix), htmlParser->content + start_index, end_index - start_index);

    struct IncomingResponse *response = api_read(absolute_url, NULL, 0);
    if (response->status == RESPONSE_NOT_FOUND) {
        return 0;
    }
    printf("%s\n", response_to_file_single_path(response, url));
    htmlParser->total_downloads++;
    return 1;
}

