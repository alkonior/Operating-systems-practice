cmake_minimum_required(VERSION 3.16)
project(Task6 C)

set(CMAKE_C_STANDARD 11)
add_library(xor src/xor.c)
add_library(fletcher src/fletcher.c)
add_library(crc16 src/crc16.c)

add_executable(Task6
        main.c
        #src/shifr.c
        #src/crcshifrchecker.c

        )

target_link_libraries(Task6 xor fletcher crc16)