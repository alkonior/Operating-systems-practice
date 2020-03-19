cmake_minimum_required(VERSION 3.13)
project(task1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)# Сообщаем cmake куда нужно проводить итоговую сборку

add_library(testlib src/lib.h)                                # Сообщаем cmake о библеотеке testlib из файла src/lib.h

add_executable(task1 src/main.c)                              # Сообщаем cmake о итоговой цели сборки task1 из файла src/main.c

set_target_properties(testlib PROPERTIES LINKER_LANGUAGE C)   # Сообщаем cmake как нужно линковать библиотеку testlib

target_link_libraries(task1 testlib)                          # Добавляем библиотеку к нашему исполняемому файлу