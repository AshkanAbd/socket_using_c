cmake_minimum_required(VERSION 3.14)
project(socket_server C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(socket_server
        main.c
        Core/Socket/server_socket.h Core/Socket/server_socket.c
        Core/Socket/client.h Core/Socket/client.c
        Core/IO/incoming_request.h Core/IO/incoming_request.c
        Core/IO/outgoing_response.h Core/IO/outgoing_response.c
        Core/Router/router.h Core/Router/router.c
        Core/Router/route_template.h Core/Router/route_template.c
        Core/Pipeline/pipeline.h Core/Pipeline/pipeline.c
        routes/routers.c
        Core/db/sqlite/sqlite3.h Core/db/sqlite/sqlite3.c
        Core/db/sqlite/migration.h Core/db/sqlite/migration.c
        controllers/controllers.h
        controllers/user_controller.c
        controllers/post_controller.c
        models/models.h models/models.c
        models/user.h models/user.c
        models/token.h models/token.c
        models/post.h models/post.c
        callbacks/callbacks.h
        callbacks/user_callback.c
        callbacks/post_callback.c
        callbacks/token_callback.c
        )

if (WIN32)
    target_link_libraries(socket_server wsock32 ws2_32)
endif ()

target_link_libraries(socket_server pthread)
