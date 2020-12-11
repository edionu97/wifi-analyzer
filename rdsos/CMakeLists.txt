cmake_minimum_required(VERSION 3.17)
project(rdsos)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        rdsos main.cpp
        utils/command_runner/headers/cmd_runner.h
        utils/command_runner/sources/cmd_runner.cpp
        utils/string_helpers/sources/string_helpers.cpp
        utils/string_helpers/headers/string_helpers.h
        utils/wifi_analyzer/sources/wifi_helpers.cpp
        utils/wifi_analyzer/headers/wifi_helpers.h
        resources/resources_manager/sources/resources_manager.cpp
        resources/resources_manager/headers/resources_manager.h)

include_directories("/usr/include/iwlib.h")
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.so")
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.a")
