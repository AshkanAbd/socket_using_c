cmake_minimum_required(VERSION 3.14)
project(socket_server C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(socket_server
        main.c
        Core/Socket/server_socket.c Core/Socket/server_socket.h
        Core/Socket/client.h Core/Socket/client.c
        Core/IO/incoming_request.h Core/IO/incoming_request.c Core/IO/outgoing_response.h Core/IO/outgoing_response.c Core/Router/router.h Core/Router/router.c Core/Router/route_template.h Core/Router/route_template.c routes/routers.c controllers/base_controller.c)

if (WIN32)
    target_link_libraries(socket_server wsock32 ws2_32)
endif ()

target_link_libraries(socket_server pthread)
