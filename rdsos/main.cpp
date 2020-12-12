#include <string>
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include "utils/wifi_analyzer/headers/wifi_helpers.h"
#include "resources/resources_manager/headers/resources_manager.h"
#include "analyzer/headers/wifi_analyzer.h"
#include "analyzer/scan_result/wireless_scan_result.h"
#include "server/headers/ws_broadcast_server.h"

int main()
{
    //declare the server
    ws_broadcast_server web_socket_broadcast_server{};

    //declare the resources manager
    const auto manager = resources_manager();

    //this represents the callback that will be called when a list of wifi scans is complete
    auto on_results_callback = [&](const std::vector<wireless_scan_result> &a) -> void
    {
        for (const auto &result : a)
        {
            web_socket_broadcast_server.broadcast_message(result.ssid.value());
            std::cout << result.ssid.value() << '\n';
        }

        //std::cout << '\n';
    };

    //instantiate the analyzer
    wifi_analyzer analyzer{"wlp0s20f3", manager, on_results_callback};

    //start the scanning async
    analyzer.start_scanning_async();

    //run the server
    web_socket_broadcast_server.run(9002);
}
