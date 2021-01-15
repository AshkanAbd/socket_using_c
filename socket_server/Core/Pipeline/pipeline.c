#include "pipeline.h"
#include "../Router/router.h"

void init_pipeline(Pipeline *pipeline) {
    pipeline->route_count = 0;

    pipeline->static_files_prefix = NULL;

    pipeline->templates = malloc(1024 * sizeof(RouteTemplate));
    memset(pipeline->templates, 0, 1024 * sizeof(RouteTemplate));

    registerRoutes(pipeline);
}

void set_root_dir(Pipeline *pipeline, const char *root_dir) {
    pipeline->static_files_prefix = malloc(strlen(root_dir) + 1);
    memset(pipeline->static_files_prefix, 0, strlen(root_dir) + 1);
    memcpy(pipeline->static_files_prefix, root_dir, strlen(root_dir));
}

RouteTemplate *match_request(Pipeline *pipeline, IncomingRequest *request) {
    RouteTemplate *template = NULL;
    register int i;
    for (i = 0; i < pipeline->route_count; ++i) {
        RouteTemplate *tmp = pipeline->templates + i;
        if (check_route(tmp, request)) {
            if (check_action(tmp, request)) {
                return tmp;
            }
            template = tmp;
        }
    }
    return template;
}

int check_route(RouteTemplate *template, IncomingRequest *request) {
    if (strcmp(template->route, request->route) == 0) {
        return 1;
    }
    return 0;
}

int check_action(RouteTemplate *template, IncomingRequest *request) {
    if (template->action == request->action) {
        return 1;
    }
    return 0;
}

void extract_request_content(void *content, int content_size, char ***argv, int *argc) {
    if (content_size == 0) {
        return;
    }

    *argv = malloc(content_size);
    memset(*argv, 0, content_size);
    *argc = 0;
    int *body_end_index = malloc(sizeof(int) * content_size);
    memset(body_end_index, 0, sizeof(int) * content_size);

    for (int i = 0; i < content_size; ++i) {
        if (*((char *) content + i) == 0x1E) {
            *(body_end_index + *argc) = i;

            int pre_body_index;
            if (*argc == 0) {
                pre_body_index = 0;
            } else {
                pre_body_index = *(body_end_index + *argc - 1) + 1;
            }

            *((*argv) + *argc) = malloc(i - pre_body_index + 1);
            memset(*((*argv) + *argc), 0, i - pre_body_index + 1);
            memcpy(*((*argv) + *argc), content + pre_body_index, i - pre_body_index);

            (*argc)++;
        }
    }
    free(body_end_index);
    if (*argc == 0) {
        return;
    }

    int body_argv_size = 1;
    for (int i = 0; i < *argc; ++i) {
        body_argv_size += strlen(*((*argv) + i)) + 1;
    }
    **argv = realloc(**argv, body_argv_size);
}

OutgoingResponse *execute_controller(IncomingRequest *request, RouteTemplate *template) {
    char **param = 0;
    int param_count = 0;
    extract_request_content(request->param, request->param_size, &param, &param_count);

    char **body = 0;
    int body_count = 0;
    extract_request_content(request->body, request->body_size, &body, &body_count);

    return (*template->func)(param, param_count, body, body_count);
}

int request_static_files(Pipeline *pipeline, IncomingRequest *request) {
    if (request->action != RESPONSE_OK) {
        return 0;
    }
    char *file_path = malloc(strlen(pipeline->static_files_prefix) + strlen(request->route) + 1);
    memset(file_path, 0, strlen(pipeline->static_files_prefix) + strlen(request->route) + 1);
    memcpy(file_path, pipeline->static_files_prefix, strlen(pipeline->static_files_prefix));
    memcpy(file_path + strlen(pipeline->static_files_prefix), request->route, strlen(request->route));

    struct stat *stat_buffer = malloc(sizeof(struct stat));
    memset(stat_buffer, 0, sizeof(struct stat));

    stat(file_path, stat_buffer);
    if (S_ISREG(stat_buffer->st_mode)) {
        free(file_path);
        free(stat_buffer);
        return 1;
    }
    free(file_path);
    free(stat_buffer);
    return 0;
}

void serve_static_file(OutgoingResponse *response, Pipeline *pipeline, IncomingRequest *request,
                       Client *client) {
    char *file_path = malloc(strlen(pipeline->static_files_prefix) + strlen(request->route) + 1);
    memset(file_path, 0, strlen(pipeline->static_files_prefix) + strlen(request->route) + 1);
    memcpy(file_path, pipeline->static_files_prefix, strlen(pipeline->static_files_prefix));
    memcpy(file_path + strlen(pipeline->static_files_prefix), request->route, strlen(request->route));

    FILE *static_file = fopen(file_path, "rb");
    fseek(static_file, 0, SEEK_END);
    int file_size = ftell(static_file);
    fseek(static_file, 0, SEEK_SET);

    int max_each_response = MAX - 4;
    char *buffer = NULL;

    int current_read = 0;
    int count = 0;
    response->status = RESPONSE_OK;
    response->data_size = max_each_response;

    while (1) {

        if (response->data != NULL) {
            free(response->data);
        }
        if (buffer != NULL) {
            free(buffer);
        }

        response->data = malloc(max_each_response);
        memset(response->data, 0, max_each_response);

        buffer = malloc(max_each_response);
        memset(buffer, 0, max_each_response);

        fread(buffer, sizeof(char), max_each_response, static_file);

        memmove(response->data, buffer, max_each_response);
        count++;
        current_read += max_each_response;
        if (current_read >= file_size) {
            response->data_size = file_size - (current_read - max_each_response);
            send_to_client(response, client, 1);
            break;
        }
        send_to_client(response, client, 0);
        if (!wait_for_client(client)) {
            break;
        }
    }
    if (buffer != NULL) {
        free(buffer);
    }
    fclose(static_file);
    free(file_path);
    printf("sent packet count: %d\n", count);
}

int wait_for_client(Client *client) {
    char *tmp = malloc(3);
    memset(tmp, 0, 3);
    do {
        recv(*client->socket, tmp, 3, 0);
        if (strlen(tmp) == 0) {
            free(tmp);
            printf("dc");
            return 0;
        }
    } while (*tmp != 48);
    free(tmp);
    return 1;
}
