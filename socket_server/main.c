#include "Core/Socket/server_socket.h"
#include "Core/Pipeline/pipeline.h"

#define MAX 1024
#define PORT 8080

void *handle_client(void *obj);

void init_server(struct ServerSocket *server_socket);

struct Client *clients;
int clientIndex = 0;

struct Pipeline *pipeline;

int main() {
    struct ServerSocket server_socket;

    clients = malloc(MAX * sizeof(struct Client));
    memset(clients, 0, MAX * sizeof(struct Client));

    pipeline = malloc(sizeof(struct Pipeline));
    memset(pipeline, 0, sizeof(struct Pipeline));

    init_server(&server_socket);
    init_pipeline(pipeline);
    set_root_dir(pipeline, "../root");

    while (1) {
        int connection = accept_connection(&server_socket);
        printf("connected %d\n", connection);
        if (connection < 0) {
            printf("Failed to accept connection\n");
            printf("Error= %d:%s\n", connection, strerror(connection));
        } else {
            struct Client *client = (clients + clientIndex++);
            init_client(client, MAX, &connection);
            pthread_t receive_thread;
            pthread_create(&receive_thread, NULL, handle_client, client);
        }
    }
}

void init_server(struct ServerSocket *server_socket) {
    int error;
    if ((error = create_socket(server_socket)) != 0) {
        printf("Failed to create socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
        exit(0);
    } else {
        printf("Socket created...\n");
    }

    assign_port(server_socket, PORT);

    if ((error = bind_socket(server_socket)) != 0) {
        printf("Fail to bind socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Socket bound...\n");
    }

    if ((error = listen_socket(server_socket)) != 0) {
        printf("Failed to listen socket\n");
        printf("Error= %d:%s\n", error, strerror(error));
    } else {
        printf("Start to listen...\n");
    }

}

void *handle_client(void *obj) {
    struct Client *client = (struct Client *) obj;

    char *buffer = malloc(MAX);
    memset(buffer, 0x1D, MAX);
    *(buffer + MAX) = 0;
    recv(*client->socket, buffer, MAX, 0);

    struct IncomingRequest request;
    struct OutgoingResponse *response = malloc(sizeof(struct OutgoingResponse));
    memset(response, 0, sizeof(struct OutgoingResponse));
    if (!parse_request(&request, buffer, MAX)) {
        init_invalid_syntax(response, NULL, 0);
    } else {
        struct RouteTemplate *routeTemplate = match_request(pipeline, &request);
        if (request_static_files(pipeline, &request)) {
            serve_static_file(response, pipeline, &request, client);
            return NULL;
        } else if (routeTemplate == NULL) {
            init_not_found(response, NULL, 0);
        } else if (routeTemplate->action != request.action) {
            init_invalid_action(response, NULL, 0);
        } else {
            memmove(response, execute_controller(&request, routeTemplate), sizeof(struct OutgoingResponse));
        }
    }
    send_to_client(response, client);

    close_client(client);
}
