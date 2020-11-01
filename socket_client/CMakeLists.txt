cmake_minimum_required(VERSION 3.14)
project(socket_client C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(socket_client
        main.c
        Core/Socket/client_socket.h Core/Socket/client_socket.c
        Core/Socket/client.h Core/Socket/client.c
        Core/IO/outgoing_request.h Core/IO/outgoing_request.c
        Core/IO/incoming_response.h Core/IO/incoming_response.c
        Core/Api/api.h Core/Api/api.c)

if (WIN32)
    target_link_libraries(socket_client wsock32 ws2_32)
endif ()

target_link_libraries(socket_client pthread)
