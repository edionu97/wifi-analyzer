//
// Created by eduard on 11.12.2020.
//

#include "../headers/resources_manager.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>

resources_manager::resources_manager()
{
    manufacturers_ = get_manufacturers();
}

std::string resources_manager::get_manufacturer_name(const std::string &mac_address) const
{
    //create the regex
    std::regex required_data{"^(..:..:..).*$"};
    std::smatch match;

    //if the mac address does not respect the regex than return the unknown
    if (!std::regex_search(mac_address, match, required_data))
    {
        return "Unknown";
    }

    //get the manufacturer bytes (group 1_
    const auto manufacturer_bytes = match[1].str();

    //get the iterator
    const auto it = manufacturers_.find(manufacturer_bytes);

    //check if the manufacturer appear in list
    if (it == manufacturers_.end())
    {
        return "Unknown";
    }

    //return its name
    return it->second;
}

std::map<std::string, std::string> resources_manager::get_manufacturers()
{
    //declare the output file
    std::ifstream in_file{"../resources/oui.txt"};

    //instantiate the map
    std::map<std::string, std::string> mac_manufacturers_association{};

    //declare the hex regex
    std::regex hex_regex{"^(.*)\\(hex\\)(.*)"};

    //declare the line matcher
    std::smatch line_match{};

    //read line by line
    std::string line{};
    while (std::getline(in_file, line))
    {
        //if the line does not respect the regex than ignore it
        if (!std::regex_search(line, line_match, hex_regex))
        {
            continue;
        }

        //count the number of matches
        if (line_match.size() != 3)
        {
            continue;
        }

        //get the mac address
        const auto mac_address = boost::algorithm::trim_copy(
                std::regex_replace(std::string{line_match[1]}, std::regex("-"), ":"));

        //get the manufacturer
        const auto manufacturer = boost::algorithm::trim_copy(std::string{line_match[2]});

        //if there are more than one manufacturer
        if (mac_manufacturers_association.find(mac_address) != mac_manufacturers_association.end())
        {
            mac_manufacturers_association[mac_address] += " + " + manufacturer;
            continue;
        }

        //insert the values in the map
        mac_manufacturers_association.insert({mac_address, manufacturer});
    }

    return mac_manufacturers_association;
}

