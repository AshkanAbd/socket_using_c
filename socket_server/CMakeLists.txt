cmake_minimum_required(VERSION 3.14)
project(socket_server C)

set(CMAKE_C_STANDARD 99)

add_executable(socket_server
        main.c
        Core/server_socket.c Core/server_socket.h
        Core/client.h Core/client.c
        )

if (WIN32)
    target_link_libraries(socket_server wsock32 ws2_32)
endif ()

target_link_libraries(socket_server pthread)
