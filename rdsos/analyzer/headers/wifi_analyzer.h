//
// Created by eduard on 12.12.2020.
//

#ifndef RDSOS_WIFI_ANALYZER_H
#define RDSOS_WIFI_ANALYZER_H

#include "../../resources/resources_manager/headers/resources_manager.h"
#include "../scan_result/wireless_scan_result.h"


#include <string>
#include <iwlib.h>
#include <optional>
#include <functional>


class wifi_analyzer
{
public:

    /**
     * This represents the class constructor
     * @param interface_name: the name of the wifi-interface
     */
    wifi_analyzer(const std::string &interface_name,
                  const resources_manager &resources_manager,
                  const std::function<void(std::vector<wireless_scan_result> &)> &on_results_available);

    /**
     * This method starts scanning the interface name
     */
    void start_scanning() const;

    /**
     * Destructor of the class
     */
    ~wifi_analyzer();

private:
    const std::string &interface_name_;
    const resources_manager &resources_manager_;
    const std::function<void(std::vector<wireless_scan_result> &)> &on_results_callback_;

    iwrange range_metadata_{};
    std::optional<int> kernel_socket_{};
};


#endif //RDSOS_WIFI_ANALYZER_H
