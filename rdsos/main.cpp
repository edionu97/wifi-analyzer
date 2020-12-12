#include <cstdio>
#include <iwlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "utils/command_runner/headers/cmd_runner.h"
#include "utils/string_helpers/headers/string_helpers.h"
#include "utils/wifi_analyzer/headers/wifi_helpers.h"
#include "resources/resources_manager/headers/resources_manager.h"
#include "analyzer/headers/wifi_analyzer.h"
#include "analyzer/scan_result/wireless_scan_result.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

#include <functional>

std::ostream &operator<<(std::ostream &out, const wifi::encryption_information &information)
{
    if (information.has_encryption.has_value())
    {
        out << boost::format("Encryption key: %s")
               % (information.has_encryption.value() ? "on" : "off");
    }

    if (information.encryption_type.has_value())
    {
        out << boost::format(" (%s)\n")
               % boost::algorithm::join(information.encryption_type.value(), ", ");
    }

    return out;
}

std::ostream &operator<<(std::ostream &out, const wireless_scan_result &information)
{

    if (information.ssid.has_value())
    {
        out << "SSID: " << information.ssid.value() << '\n';
    }

    if (information.mac_address.has_value())
    {
        out << "MAC address: " << information.mac_address.value() << '\n';
    }

    if (information.manufacturer.has_value())
    {
        out << "Manufacturer: " << information.manufacturer.value() << '\n';
    }

    if (information.quality.has_value())
    {
        out << boost::format("Quality: %d/%d\n")
               % information.quality.value()
               % information.max_quality.value();

    }

    if (information.frequency.has_value())
    {
        out << boost::format("Frequency: %s\n") % information.frequency.value();
    }

    if (information.channel.has_value())
    {
        out << boost::format("Channel: %s\n") % information.channel.value();
    }

    if (information.signal.has_value())
    {
        out << boost::format("Signal: %s\n") % information.signal.value();
    }

    if (information.mode.has_value())
    {
        out << boost::format("Mode: %s\n") % information.mode.value();
    }

    if (information.encryption.has_value())
    {
        out << information.encryption.value() << '\n';
    }

    return out;
}


//iwlist interface scan
int main()
{
    const auto manager = resources_manager();

    auto on_results_callback = [](const std::vector<wireless_scan_result> &a) -> void
    {
        for (const auto &result : a)
        {
            std::cout << result << '\n';
        }

        std::cout << '\n';
    };

    wifi_analyzer analyzer{"wlp0s20f3", manager, on_results_callback};

    analyzer.start_scanning_async();
}
