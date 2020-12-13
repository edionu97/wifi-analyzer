cmake_minimum_required(VERSION 3.17)
project(rdsos)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

include(FindPCAP.cmake)
include_directories("/usr/include/")

add_executable(
        rdsos main.cpp
        utils/command_runner/headers/cmd_runner.h
        utils/command_runner/sources/cmd_runner.cpp
        utils/string_helpers/sources/string_helpers.cpp
        utils/string_helpers/headers/string_helpers.h
        utils/wifi_analyzer/sources/wifi_helpers.cpp
        utils/wifi_analyzer/headers/wifi_helpers.h
        resources/resources_manager/sources/resources_manager.cpp
        resources/resources_manager/headers/resources_manager.h
        analyzer/sources/wifi_analyzer.cpp
        analyzer/headers/wifi_analyzer.h
        analyzer/scan_result/wireless_scan_result.cpp
        analyzer/scan_result/wireless_scan_result.h
        server/sources/ws_broadcast_server.cpp
        server/headers/ws_broadcast_server.h
        ${SOURCE_FILES})

target_link_libraries(rdsos ${PCAP_LIBRARY})
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.so")
target_link_libraries(rdsos "/usr/lib/x86_64-linux-gnu/libiw.a")

