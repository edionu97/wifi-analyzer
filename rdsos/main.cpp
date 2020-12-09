#include <cstdio>
#include <iwlib.h>
#include <string>

#define clear() printf("\033[H\033[J")

int main()
{
    wireless_scan_head head;
    wireless_scan *result;
    iwrange range;
    int sock;

    /* Open socket to kernel */
    sock = iw_sockets_open();

    while(true)
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
            printf("%s\n", result->b.essid);
            result = result->next;
        }

        sleep(1);
    }
}
