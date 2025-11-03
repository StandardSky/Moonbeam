cmake_minimum_required(VERSION 3.23)

project(custom_server_client)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/server.c
)

add_executable(server ${SRC_FILES})
target_compile_options(server PRIVATE -Werror -Wall -Wpedantic)