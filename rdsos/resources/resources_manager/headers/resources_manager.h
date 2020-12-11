//
// Created by eduard on 11.12.2020.
//

#ifndef RDSOS_RESOURCES_MANAGER_H
#define RDSOS_RESOURCES_MANAGER_H


#include <string>
#include <map>

class resources_manager
{
public:

    resources_manager();

    /**
     * This function is responsible for getting a manufacturer name by the product MAC address
     * @param mac_address: the mac address
     * @return a string representing the name of the manufacturer
     */
    std::string get_manufacturer_name(const std::string &mac_address) const;

private:

    /**
     * This method it is used for getting the manufacturers
     * @return a map that represents the manufacturers
     */
    static std::map<std::string, std::string> get_manufacturers();

    std::map<std::string, std::string> manufacturers_;
};


#endif //RDSOS_RESOURCES_MANAGER_H
