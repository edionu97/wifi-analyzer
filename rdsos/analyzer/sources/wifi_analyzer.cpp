//
// Created by eduard on 12.12.2020.
//

#include "../headers/wifi_analyzer.h"
#include "../../utils/wifi_analyzer/headers/wifi_helpers.h"
#include "../scan_result/wireless_scan_result.h"
#include <stdexcept>
#include <future>
#include <functional>
#include <iostream>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

void
wifi_analyzer::start_scanning() const
{
    try
    {
        while (true)
        {
            std::vector<wireless_scan_result> results{};

            //get the encryption information
            const auto encryption_information = wifi::wifi_helpers::get_encryption_information(interface_name_);

            /* Perform the scan */
            wireless_scan_head head{};
            if (iw_scan(kernel_socket_.value(),
                        const_cast<char *>(interface_name_.c_str()),
                        range_metadata_.we_version_compiled, &head) < 0)
            {
                throw std::runtime_error("Error while scanning the interface, aborting...");
            }

            //get a pointer to the wifi info structure
            std::shared_ptr<wireless_scan> wifi_result(head.result);
            while (wifi_result != nullptr)
            {
                //get the wireless information
                const auto wireless_information = wireless_scan_result::complete_scan_result(*wifi_result,
                                                                                             range_metadata_,
                                                                                             resources_manager_,
                                                                                             encryption_information);
                //add the results in the configuration
                results.push_back(wireless_information);


                //move to next result and deallocate the previous node
                wifi_result = std::shared_ptr<wireless_scan>(wifi_result->next);
            }

            //call the callback
            on_results_callback_(results);
            return;
        }
    } catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }

}

wifi_analyzer::wifi_analyzer(
        const std::string &interface_name,
        const resources_manager &resources_manager,
        const std::function<void(std::vector<wireless_scan_result> &)> &on_results_available)
        : interface_name_{interface_name},
          on_results_callback_{on_results_available},
          resources_manager_{resources_manager}
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


