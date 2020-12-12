//
// Created by eduard on 12.12.2020.
//

#ifndef RDSOS_WIFI_ANALYZER_H
#define RDSOS_WIFI_ANALYZER_H


#include <string>
#include <iwlib.h>
#include <optional>
#include "../../resources/resources_manager/headers/resources_manager.h"


class wifi_analyzer
{
public:

    /**
     * This represents the class constructor
     * @param interface_name: the name of the wifi-interface
     */
    wifi_analyzer(const std::string &interface_name, const resources_manager& resources_manager);

    /**
     * This method starts scanning the interface name
     */
    void start_scanning() const;

    /**
     * Destructor of the class
     */
    ~wifi_analyzer();

private:
    const std::string& interface_name_;
    const resources_manager& resources_manager_;

    iwrange range_metadata_{};
    std::optional<int> kernel_socket_{};
};


#endif //RDSOS_WIFI_ANALYZER_H
