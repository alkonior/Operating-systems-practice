cmake_minimum_required(VERSION 3.16)
project(Task13 C)

set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_FLAGS -pthread)

add_library(queue queue/queue.h queue/queue.c)
add_library(queue_m queue/queue.h queue/queue_mutex.c)
add_library(queue_cv queue/queue.h queue/queue_cond.c)
add_library(utils queue/utils.h queue/utils.c)

add_executable(queue_test main.c)
target_link_libraries(queue_test PUBLIC queue utils)

add_executable(queue_mutex_test main.c)
target_link_libraries(queue_mutex_test PUBLIC queue_m utils)

add_executable(queue_cv_test main.c)
target_link_libraries(queue_cv_test PUBLIC queue_cv utils)