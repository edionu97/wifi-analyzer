#include <cstdio>
#include <iwlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "utils/command_runner/headers/cmd_runner.h"
#include "utils/string_helpers/headers/string_helpers.h"
#include "utils/wifi_analyzer/headers/wifi_helpers.h"
#include "resources/resources_manager/headers/resources_manager.h"


//iwlist interface scan
int main()
{

    auto manager = resources_manager{};

    std::cout << manager.get_manufacturer_name("aa:bb:cc:dd:ee") << '\n';

    auto value = wifi::wifi_helpers::get_encryption_information("wlp0s20f3");

    return 0;


    if (value["58:D9:D5:8C:77:E1"].has_encryption.has_value())
    {
        std::cout << std::boolalpha << value["58:D9:D5:8C:77:E1"].has_encryption.value() << '\n';
    }

    for (auto el : value["58:D9:D5:8C:77:E1"].encryption_type.value())
    {
        std::cout << el << '\n';
    }


    return 0;
//    wireless_scan_head head;
//    wireless_scan *result;
//    iwrange range;
//    int sock;
//
//    /* Open socket to kernel */
//    sock = iw_sockets_open();
//
//    while (true)
//    {
//        std::string wlan_name{"wlp0s20f3"};
//
//        /* Get some metadata to use for scanning */
//        if (iw_get_range_info(sock, wlan_name.c_str(), &range) < 0)
//        {
//            printf("Error during iw_get_range_info. Aborting.\n");
//            exit(2);
//        }
//
//        /* Perform the scan */
//        if (iw_scan(sock, const_cast<char *>(wlan_name.c_str()), range.we_version_compiled, &head) < 0)
//        {
//            printf("Error during iw_scan. Aborting.\n");
//            exit(2);
//        }
//
//        /* Traverse the results */
//        result = head.result;
//        while (nullptr != result)
//        {
//
////            //ssid
////            printf("SSID: %s\n", result->b.essid);
////
////            //mac address
////            printf("MAC access point: ");
////            for (int i = 0; i < strlen(result->ap_addr.sa_data); ++i, printf("."))
////            {
////                printf("%02X", (unsigned char) result->ap_addr.sa_data[i]);
////            }
////
////            //get the quality percentage
////            printf("Quality: %d/%d\n", result->stats.qual.qual, range.max_qual.qual);
////
////            //get the frequency (get the shortest representation)
////            printf("Frequency: %.10g Ghz\n", result->b.freq / 1000000000);
////
////            //get the channel
////            printf("Channel: %d\n", iw_freq_to_channel(result->b.freq, &range));
////
////            //get the signal level
////            printf("Signal level: %d dBm (higher is better)\n", (int8_t) result->stats.qual.level);
////
////            //for manufacturer search the file obtained from wget http://standards-oui.ieee.org/oui/oui.txt
////
////            if(result->b.has_mode)
////            {
////                //get the mode
////                printf("Mode: %s\n", iw_operation_mode[result->b.mode]);
////            }
//
//
//            iwreq wrq{};
//
//            std::cout << iw_get_ext(sock, const_cast<char *>(wlan_name.c_str()), SIOCGIWENCODE, &wrq) << '\n';
//
//
//            result = result->next;
//        }
//
//        return 0;
//
//        sleep(1);
}
