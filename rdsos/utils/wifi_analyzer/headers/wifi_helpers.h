//
// Created by eduard on 11.12.2020.
//

#ifndef RDSOS_WIFI_HELPERS_H
#define RDSOS_WIFI_HELPERS_H

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

namespace wifi
{
    struct encryption_information
    {
        std::optional<bool> has_encryption;
        std::optional<std::vector<std::string>> encryption_type;
    };

    class wifi_helpers
    {
    public:

        /**
         * This function it is used for getting the information about encryption
         * @param interface_name: the name of the wifi interface
         * @return an association between the mac addresses and the required information
         */
        static std::map<std::string, encryption_information>
        get_encryption_information(const std::string &interface_name);
    };
}


#endif //RDSOS_WIFI_HELPERS_H
