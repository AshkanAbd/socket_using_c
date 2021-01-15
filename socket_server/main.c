#include "Core/Socket/server_socket.h"
#include "Core/Pipeline/pipeline.h"
#include "Core/db/sqlite/migration.h"

int PORT = 8080;
char *db_path = "../db/app.sqlite";

void check_args(int argc, char **argv);

void *handle_client(void *obj);

void init_server(ServerSocket *server_socket);

Pipeline *pipeline;

int main(int argc, char **argv) {
    check_args(argc, argv);
    ServerSocket server_socket;

    pipeline = malloc(sizeof(Pipeline));
    memset(pipeline, 0, sizeof(Pipeline));

    init_database(db_path);

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
            Client *client = malloc(sizeof(Client));
            memset(client, 0, sizeof(Client));
            init_client(client, &connection);
            pthread_t receive_thread;
            pthread_create(&receive_thread, NULL, handle_client, client);
        }
    }
}

void init_server(ServerSocket *server_socket) {
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
    Client *client = (Client *) obj;

    char *buffer = malloc(MAX + 1);
    memset(buffer, 0x1D, MAX + 1);
    *(buffer + MAX) = 0;
    recv(*client->socket, buffer, MAX, 0);

    IncomingRequest *request = malloc(sizeof(IncomingRequest));
    memset(request, 0, sizeof(IncomingRequest));
    OutgoingResponse *response = malloc(sizeof(OutgoingResponse));
    memset(response, 0, sizeof(OutgoingResponse));
    if (!parse_request(request, buffer, MAX)) {
        init_invalid_syntax(response, NULL, 0);
    } else {
        if (request_static_files(pipeline, request)) {
            serve_static_file(response, pipeline, request, client);
            goto close_client;
        }
        RouteTemplate *route_template = match_request(pipeline, request);
        if (route_template == NULL) {
            init_not_found(response, NULL, 0);
        } else if (route_template->action != request->action) {
            init_invalid_action(response, NULL, 0);
        } else {
            OutgoingResponse *controller_response = execute_controller(request, route_template);
            memmove(response, controller_response, sizeof(OutgoingResponse));
            free(controller_response);
        }
    }
    send_to_client(response, client, 1);

    close_client:
    free(buffer);
    free(request);
    if (response->data != NULL) {
        free(response->data);
    }
    free(response);
    close_client(client);
}

void check_args(int argc, char **argv) {
    if (argc > 1 && (strcmp(*(argv + 1), "--help") == 0 || strcmp(*(argv + 1), "-h") == 0)) {
        printf("socket_server.exe [sqlite_db_path] [port] [packet_size]");
        exit(1);
    }

    if (argc >= 2) {
        db_path = *(argv + 1);
    }

    if (argc >= 3) {
        PORT = atoi(*(argv + 2));
    }

    if (argc >= 2) {
        change_max(atoi(*(argv + 3)));
    }
}