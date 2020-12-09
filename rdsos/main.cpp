#include <cstdio>
#include <iwlib.h>
#include <string>
#include <cstring>


//iwlist interface scan
int main()
{
    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    int sock;

    /* Open socket to kernel */
    sock = iw_sockets_open();

    while (true)
    {
        std::string wlan_name{"wlp0s20f3"};

        /* Get some metadata to use for scanning */
        if (iw_get_range_info(sock, wlan_name.c_str(), &range) < 0)
        {
            printf("Error during iw_get_range_info. Aborting.\n");
            exit(2);
        }

        /* Perform the scan */
        if (iw_scan(sock, const_cast<char *>(wlan_name.c_str()), range.we_version_compiled, &head) < 0)
        {
            printf("Error during iw_scan. Aborting.\n");
            exit(2);
        }

        /* Traverse the results */
        result = head.result;
        while (nullptr != result)
        {
            printf("\n");

            //ssid
            printf("SSID: %s\n", result->b.essid);

            //mac address
            printf("MAC access point: ");
            for (int i = 0; i < strlen(result->ap_addr.sa_data); ++i, printf("."))
            {
                printf("%02X", (unsigned char) result->ap_addr.sa_data[i]);
            }

            printf("\n");
            //get the quality percentage
            printf("Quality: %d/%d\n", result->stats.qual.qual, range.max_qual.qual);

            //get the frequency (get the shortest representation)
            printf("Frequency: %.10g Ghz\n", result->b.freq / 1000000000);

            //get the channel
            printf("Channel: %d\n", iw_freq_to_channel(result->b.freq, &range));

            //get the signal level
            printf("Signal level: %d dBm (higher is better)\n", (int8_t) result->stats.qual.level);

            result = result->next;
        }

        return 0;

        sleep(1);
    }
}
