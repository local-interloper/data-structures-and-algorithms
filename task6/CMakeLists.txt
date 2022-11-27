project("spa")

cmake_minimum_required(VERSION 3.22)

file(GLOB FILES src/*.c)

add_executable(${PROJECT_NAME} ${FILES})

target_include_directories(${PROJECT_NAME} PRIVATE xd)