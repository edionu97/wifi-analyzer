//
// Created by eduard on 11.12.2020.
//

#include <regex>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "../headers/wifi_helpers.h"
#include "../../command_runner/headers/cmd_runner.h"
#include "../../string_helpers/headers/string_helpers.h"

std::map<std::string, wifi::encryption_information>
wifi::wifi_helpers::get_encryption_information(const std::string &interface_name)
{
    //build the cmd string
    const auto cmd_string = std::string{}
            .append("iwlist ")
            .append(interface_name)
            .append(" scan");

    //execute the command
    const auto iwlist_command_result = cmd_runner::execute_command(cmd_string);

    //define the regex
    const std::regex mac_address_regex{"Address: (..:..:..:..:..:..)\n"};

    //get the map association (max addresses and the information)
    const auto mac_address_information = string_helpers::get_text_between_tokens(mac_address_regex,
                                                                                 iwlist_command_result, 1);

    //information map
    std::map<std::string, wifi::encryption_information> mac_address_info;

    //iterate through the map
    for (const auto &wifi_information : mac_address_information)
    {
        //get the mac address and its related information
        const auto &mac_address = wifi_information.first;
        const auto &mac_address_related_information = wifi_information.second;

        //get the encryption info
        wifi::encryption_information encryption_info{};

        //split all the results into multiple lines
        for (const auto &string_token : string_helpers::tokenize_string(mac_address_related_information, '\n'))
        {
            //trim the token
            const auto trimmed_token = boost::algorithm::trim_copy(string_token);

            //if the line is encryption line
            if (boost::algorithm::contains(trimmed_token, "Encryption key:"))
            {
                encryption_info.has_encryption = !boost::algorithm::contains(trimmed_token, ":off");
            }

            //if the line contains WPA information
            if (boost::algorithm::contains(trimmed_token, "WPA"))
            {
                //declare the wpa regex
                const auto &wpa_regex = std::regex("WPA[1-3]*");

                //get the match
                std::smatch match{};
                if (!std::regex_search(trimmed_token, match, wpa_regex))
                {
                    continue;
                }

                //get the value
                auto value = (encryption_info.encryption_type.value_or(std::vector<std::string>{}));

                //push the value
                value.push_back(match[0]);

                //set the new value
                encryption_info.encryption_type = value;
            }
        }

        //put the information in the map
        mac_address_info.insert({mac_address, encryption_info});
    }

    return mac_address_info;
}
