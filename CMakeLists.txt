cmake_minimum_required(VERSION 2.8.4)
project(Semaphore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.c sem.c )
add_executable(Semaphore ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Semaphore pthread)
