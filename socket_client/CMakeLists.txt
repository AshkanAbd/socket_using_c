cmake_minimum_required(VERSION 3.14)
project(socket_client C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

#FIND_PACKAGE(PkgConfig REQUIRED)
#PKG_CHECK_MODULES(GTK REQUIRED gtk+-3.0)
#INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIRS})
#LINK_DIRECTORIES(${GTK_LIBRARY_DIRS})

if (MSVC)
    #    add_compile_options(/W4 /WX)
else ()
    #    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

add_executable(socket_client
        main.c
        Core/Socket/client_socket.h Core/Socket/client_socket.c
        Core/Socket/client.h Core/Socket/client.c
        Core/IO/outgoing_request.h Core/IO/outgoing_request.c
        Core/IO/incoming_response.h Core/IO/incoming_response.c
        Core/Api/api.h Core/Api/api.c
        interface/interface.h interface/interface.c Core/HtmlParser/html_parser.h Core/HtmlParser/html_parser.c
        weblog/models/models.h
        weblog/models/post.h weblog/models/post.c
        weblog/life_cycle.h weblog/life_cycle.c
        weblog/apis/apis.h
        weblog/apis/auth_api.c weblog/apis/auth_api.h
        weblog/models/user.c weblog/models/user.h weblog/interface/interface.h weblog/interface/main_status.c weblog/interface/sign_in_status.c weblog/interface/sign_up_status.c)

if (WIN32)
    target_link_libraries(socket_client wsock32 ws2_32)
endif ()

target_link_libraries(socket_client pthread
        #        ${GTK_LIBRARY_DIRS}
        #        ${GTK_INCLUDE_DIRS}
        #        ${GTK_LIBRARIES}
        )
