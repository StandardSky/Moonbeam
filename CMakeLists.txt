cmake_minimum_required(VERSION 3.23)

project(moonbeam)

set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/log.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wpedantic)