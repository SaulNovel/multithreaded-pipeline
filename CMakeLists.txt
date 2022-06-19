cmake_minimum_required(VERSION 3.8)

project(task-pipeline)

set(CMAKE_CXX_STANDAR 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive -Wno-deprecated-declarations -m64 -fexceptions -g -fPIC -Wall -Wno-long-long -Wconversion -Wwrite-strings -Wsign-compare -D_GLIBCXX_DEBUG")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(pipeline)
include_directories(src)
include_directories(test)

add_subdirectory(pipeline)
add_subdirectory(src)
add_subdirectory(test)