/**
 * The file that contains HtmlParser struct.
 */
#ifndef SOCKET_CLIENT_HTML_PARSER_H
#define SOCKET_CLIENT_HTML_PARSER_H

#include "../Api/api.h"

typedef struct HtmlParser HtmlParser;

/**
 * The struct used for parsing HTML string.
 */
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

/**
 * Initialize a HtmlParses struct.
 * @param html_parser
 * @param data
 * @param data_size
 * @param ip
 * @param port
 */
void init_html_parser(HtmlParser *html_parser, char *data, unsigned long long int data_size,
                      char *ip, int port);

/**
 * Check HTML string for next image to download.
 * @param html_parser
 * @return returns 1, if a new image found and update current image pointer.
 * @return returns 0, if no more image found.
 */
int has_more_img(HtmlParser *html_parser);

/**
 * Downloads the image that index is available in img_position and increases img_position.
 * @param html_parser
 * @param prefix
 * @return returns 1, if download is successful.
 * @return returns 0, if can't download the image.
 */
int download_current_img(HtmlParser *html_parser, const char *prefix);

/**
 * Check HTML string for next JS script to download.
 * @param html_parser
 * @return returns 1, if a new script found and update current script pointer.
 * @return returns 0, if no more script found.
 */
int has_more_script(HtmlParser *html_parser);

/**
 * Downloads the script that index is available in script_position and increases script_position.
 * @param html_parser
 * @param prefix
 * @return returns 1, if download is successful.
 * @return returns 0, if can't download the script.
 */
int download_current_script(HtmlParser *html_parser, const char *prefix);

/**
 * Check HTML string for next CSS to download.
 * @param html_parser
 * @return returns 1, if a new CSS found and update current CSS pointer.
 * @return returns 0, if no more CSS found.
 */
int has_more_css(HtmlParser *html_parser);

/**
 * Downloads the CSS that index is available in css_position and increases css_position.
 * @param html_parser
 * @param prefix
 * @return returns 1, if download is successful.
 * @return returns 0, if can't download the CSS.
 */
int download_current_css(HtmlParser *html_parser, const char *prefix);

/**
 * Downloads the object from the specified position in the HTML string, which is actually the route of the object.
 * @param html_parser
 * @param prefix
 * @param start_index
 * @param end_index
 * @return
 */
int download_html_object(HtmlParser *html_parser, const char *prefix, unsigned long long int start_index,
                         unsigned long long int end_index);

#endif //SOCKET_CLIENT_HTML_PARSER_H
