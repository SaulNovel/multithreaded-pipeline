cmake_minimum_required(VERSION 3.8)

project(task-pipeline)

set(CMAKE_CXX_STANDAR 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fpermissive -Wno-deprecated-declarations -m64 -fexceptions -g -fPIC -g -Wall -Wno-long-long -Wconversion -Wwrite-strings -Wsign-compare -D_GLIBCXX_DEBUG")
# core dumps: g++ -static -pthread -D_GLIBCXX_GTHREAD_USE_WEAK=0 -std=c++0x -Wl,--whole-archive -lpthread -Wl,--no-whole-archive <yourCode.c>

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories(pipeline)
include_directories(src)

add_subdirectory(pipeline)
add_subdirectory(src)