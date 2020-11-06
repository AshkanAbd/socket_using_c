#ifndef SOCKET_SERVER_BASE64_H
#define SOCKET_SERVER_BASE64_H

#include <stdlib.h>
#include <string.h>

char *base64_encode(char *input_buffer, int input_buffer_size);

char *base64_decode(char *input_buffer);

#endif //SOCKET_SERVER_BASE64_H
