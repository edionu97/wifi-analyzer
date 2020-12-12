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

#include <nlohmann/json.hpp>

/**
 * This method it is used by the nlohmann.json lib
 * @param converted_object: the json representation
 * @param scan_result: the object that will be converted
 */
void to_json(nlohmann::json &converted_object, const wireless_scan_result &scan_result);

int main()
{
    //declare the server
    ws_broadcast_server web_socket_broadcast_server{};

    //declare the resources manager
    const auto manager = resources_manager();

    //this represents the callback that will be called when a list of wifi scans is complete
    auto on_results_callback = [&](const std::vector<wireless_scan_result> &scan_result) -> void
    {
        //create the json result
        nlohmann::json json_result{{"wifi", scan_result}};

        //serialize the json and send it through the client
        web_socket_broadcast_server.broadcast_message(json_result.dump(4));
    };

    //instantiate the analyzer
    wifi_analyzer analyzer{"wlp0s20f3", manager, on_results_callback};

    //start the scanning async
    analyzer.start_scanning_async();

    //run the server
    web_socket_broadcast_server.run(9002);
}


void to_json(nlohmann::json &converted_object, const wireless_scan_result &scan_result)
{
    //convert the object
    converted_object = nlohmann::json{};

    //the ssid
    if (scan_result.ssid.has_value())
    {
        converted_object["ssid"] = scan_result.ssid.value();
    }

    //the mac address
    if (scan_result.mac_address.has_value())
    {
        converted_object["macAddress"] = scan_result.mac_address.value();
    }

    // the quality
    if (scan_result.quality.has_value())
    {
        converted_object["quality"] = scan_result.quality.value();
    }

    //the max_quality
    if (scan_result.max_quality.has_value())
    {
        converted_object["maxQuality"] = scan_result.max_quality.value();
    }

    //the freq
    if (scan_result.frequency.has_value())
    {
        converted_object["frequency"] = scan_result.frequency.value();
    }

    //the channel
    if (scan_result.channel.has_value())
    {
        converted_object["channel"] = scan_result.channel.value();
    }

    //the signal
    if (scan_result.signal.has_value())
    {
        converted_object["signal"] = scan_result.signal.value();
    }

    //the manufacturer
    if (scan_result.manufacturer.has_value())
    {
        converted_object["manufacturer"] = scan_result.manufacturer.value();
    }

    //the mode
    if (scan_result.mode.has_value())
    {
        converted_object["mode"] = scan_result.mode.value();
    }

    //the encryption
    if (scan_result.encryption.has_value())
    {
        const auto encryption = scan_result.encryption.value();

        //the first item
        if (encryption.has_encryption.has_value())
        {
            converted_object["encryption"]["isEncrypted"] = encryption.has_encryption.value();
        }

        //the second item
        if (encryption.encryption_type.has_value())
        {
            converted_object["encryption"]["encryption"] = encryption.encryption_type.value();
        }
    }
}
