#include "incoming_request.h"

void init_request(IncomingRequest *request, int action, char *route, void *param, int param_size,
                  void *body, int body_size) {
    request->action = action;

    request->route = malloc(strlen(route));
    memcpy(request->route, route, strlen(route));

    request->param_size = param_size;
    request->param = malloc(param_size);
    memcpy(request->param, param, param_size);

    request->body_size = body_size;
    request->body = malloc(body_size);
    memcpy(request->body, body, body_size);
}

int fill(IncomingRequest *request, int state, const char *buff, int buff_size) {
    if (state == 1) {
        if (buff_size != 1 || *buff > 4 || *buff < 1) {
            return 0;
        }
        request->action = (int) *buff;
    } else if (state == 2) {
        if (buff_size == 0) {
            return 0;
        }

        request->route = malloc(buff_size + 1);
        memset(request->route, 0, buff_size);
        memcpy(request->route, buff, buff_size);
        *(request->route + buff_size) = 0;

    } else if (state == 3) {
        if (buff_size == 0) {
            return 1;
        }

        request->param = malloc(buff_size + 1);
        memset(request->param, 0, buff_size);
        memcpy(request->param, buff, buff_size);
        *((char *) (request->param + buff_size)) = 0;

        request->param_size = buff_size;
    } else if (state == 4) {
        if (buff_size == 0) {
            return 1;
        }

        request->body = malloc(buff_size + 1);
        memset(request->body, 0, buff_size);
        memcpy(request->body, buff, buff_size);
        *((char *) (request->body + buff_size)) = 0;

        request->body_size = buff_size;
    } else {
        return 0;
    }
    return 1;
}

int parse_request(IncomingRequest *request, const char *buffer, int buffer_size) {
    char *buff = malloc(buffer_size);
    memset(buff, 0, buffer_size);
    int buff_index = 0;
    int state = 1;

    register int i;
    for (i = 0; i < buffer_size; ++i) {
        char c = *(buffer + i);
        if (c != 0x1D) {
            *(buff + buff_index++) = c;
        } else {
            if (*(buffer + i) == *(buffer + i - 1) && *(buffer + i) == *(buffer + i + 1) && (i + 1 < buffer_size)) {
                break;
            }
            if (!fill(request, state, buff, buff_index)) {
                free(buff);
                return 0;
            }
            state++;
            memset(buff, 0, buffer_size);
            buff_index = 0;
        }
    }

    if (state == 1) {
        free(buff);
        return 0;
    }
    free(buff);
    if (request->route == NULL) {
        return 0;
    }
    return 1;
}
