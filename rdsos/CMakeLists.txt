cmake_minimum_required(VERSION 3.17)
project(rdsos)

set(CMAKE_CXX_STANDARD 11)

add_executable(rdsos main.cpp)

include_directories("/usr/include/iwlib.h")
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.so")
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.a")
