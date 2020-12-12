//
// Created by eduard on 12.12.2020.
//

#include "../headers/wifi_analyzer.h"
#include <stdexcept>


void wifi_analyzer::start_scanning() const
{


}

wifi_analyzer::wifi_analyzer(const std::string &interface_name, const resources_manager &resources_manager)
        : interface_name_{interface_name}, resources_manager_{resources_manager}
{
    //open the socket
    if ((kernel_socket_ = iw_sockets_open()) < 0)
    {
        throw std::runtime_error("Error opening the socket...");
    }

    //get the necessary metadata for scanning
    if (iw_get_range_info(kernel_socket_.value(), interface_name.c_str(), &range_metadata_) < 0)
    {
        throw std::runtime_error("Error when trying to get range metadata...");
    }
}

wifi_analyzer::~wifi_analyzer()
{
    //if the socket was not instantiated do nothing
    if (!kernel_socket_.has_value())
    {
        return;
    }

    //close the opened socket
    iw_sockets_close(kernel_socket_.value());
}


