cmake_minimum_required(VERSION 3.14)
project(socket_client C)

set(CMAKE_C_STANDARD 99)

add_executable(socket_client
        main.c
        Core/client_socket.h Core/client_socket.c
        Core/client.h Core/client.c
        )

if (WIN32)
    target_link_libraries(socket_client wsock32 ws2_32)
endif ()

target_link_libraries(socket_client pthread)
