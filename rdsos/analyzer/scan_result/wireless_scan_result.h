//
// Created by eduard on 12.12.2020.
//

#ifndef RDSOS_WIRELESS_SCAN_RESULT_H
#define RDSOS_WIRELESS_SCAN_RESULT_H

#define UI_SIGNAL_POWER_LINES 4


#include <optional>
#include <iwlib.h>
#include "../../utils/wifi_analyzer/headers/wifi_helpers.h"
#include "../../resources/resources_manager/headers/resources_manager.h"

struct wireless_scan_result
{
    //SSID
    std::optional<std::string> ssid{};

    //MAC
    std::optional<std::string> mac_address{};

    //QUALITY and MAX_QUALITY
    std::optional<ushort> quality{};
    std::optional<ushort> max_quality{};

    //FREQUENCY
    std::optional<double> frequency{};

    //CHANNEL
    std::optional<int> channel{};

    //SIGNAL LEVEL (dBm)
    std::optional<std::string> signal{};

    //MANUFACTURER
    std::optional<std::string> manufacturer{};

    //MODE
    std::optional<std::string> mode{};

    //ENCRYPTION
    std::optional<wifi::encryption_information> encryption{};

    /**
     * This function will create a wifi scan result instance
     * @param scan_result: the scan result
     * @param range_metadata: the range metadata
     * @param manager: the manager
     * @return an instance of scan result
     */
    static wireless_scan_result complete_scan_result(const wireless_scan &scan_result,
                                                     const iwrange &range_metadata,
                                                     const resources_manager &manager,
                                                     const std::map<std::string, wifi::encryption_information> &wifi_encryption_info);

private:
    wireless_scan_result() = default;
};


#endif //RDSOS_WIRELESS_SCAN_RESULT_H
