cmake_minimum_required(VERSION 3.16)
project(Task8 C)

set(CMAKE_C_STANDARD 11)


add_executable(client src/client.c)
add_executable(server src/server.c)

target_link_libraries(server
        PUBLIC
        "/usr/lib/x86_64-linux-gnu/librt.so"
        )
