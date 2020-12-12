//
// Created by eduard on 12.12.2020.
//

#include "wireless_scan_result.h"
#include <boost/format.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/lexical_cast.hpp>

wireless_scan_result
wireless_scan_result::complete_scan_result(const wireless_scan &scan_result,
                                           const iwrange &range_metadata,
                                           const resources_manager &manager,
                                           const std::map<std::string, wifi::encryption_information> &wifi_encryption_info)
{
    //declare the scan result
    wireless_scan_result wifi_result{};

    //set the SSID
    if (scan_result.b.has_essid)
    {
        wifi_result.ssid = std::string{scan_result.b.essid};
    }

    //set the MAC address and the
    if (scan_result.has_ap_addr)
    {
        //iterate though data
        const auto length = strlen(scan_result.ap_addr.sa_data);
        for (auto i = 0; i < length; ++i)
        {
            //add the : after each byte of data
            if (i > 0)
            {
                wifi_result.mac_address = wifi_result.mac_address.value_or("") + ":";
            }

            //convert the value to hex
            const auto value = (boost::format("%02X") %
                                static_cast<int>(static_cast<unsigned char>(scan_result.ap_addr.sa_data[i]))).str();

            //append to the mac address
            wifi_result.mac_address = wifi_result.mac_address.value_or("") + value;
        }
    }

    //get the quality percentage
    if (scan_result.has_stats)
    {
        //set the quality
        wifi_result.quality = scan_result.stats.qual.qual;
    }

    //set the max quality
    if (scan_result.has_stats)
    {
        //set the max quality
        wifi_result.max_quality = range_metadata.max_qual.qual;
    }

    //get the frequency
    if (scan_result.b.has_freq)
    {
        wifi_result.frequency = boost::lexical_cast<double>(
                (boost::format("%.10g") % (scan_result.b.freq / 1000000000)).str());
    }

    //get the channel
    if (scan_result.b.has_freq)
    {
        wifi_result.channel = iw_freq_to_channel(scan_result.b.freq, &range_metadata);
    }

    //set the signal level
    if (scan_result.has_stats)
    {
        wifi_result.signal = std::to_string((int8_t) scan_result.stats.qual.level);
    }

    //set the manufacturer
    if (wifi_result.mac_address.has_value())
    {
        wifi_result.manufacturer = manager.get_manufacturer_name(wifi_result.mac_address.value());
    }

    //set the mode
    if (scan_result.b.has_mode)
    {
        wifi_result.mode = iw_operation_mode[scan_result.b.mode];
    }

    //set the encryption
    if (wifi_result.mac_address.has_value())
    {
        //search the wifi encryption information
        const auto it = wifi_encryption_info.find(wifi_result.mac_address.value());
        if (it != wifi_encryption_info.end())
        {
            wifi_result.encryption = it->second;
        }
    }

    return wifi_result;
}
