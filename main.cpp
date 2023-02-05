#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iomanip>
#include <arpa/inet.h>
#include <cstdlib>

#include "ipv4.cpp"

const char* TUN_DEVICE = "/dev/net/tun";
const char* TUN_NAME = "tun0";

int main()
{

    int tun_fd = open(TUN_DEVICE, O_RDWR);

    if (tun_fd < 0)
    {
        std::cerr << "Failed to open tun interface" << strerror(errno) << std::endl;
        return 1;
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TUN;
    strncpy(ifr.ifr_name, TUN_NAME, IFNAMSIZ);

    if (ioctl(tun_fd, TUNSETIFF, &ifr) < 0)
    {
        perror("Failed to configure tun interface");
        return 1;
    }

    uint8_t buffer[2048];

    while (true) {

        int nbytes = read(tun_fd, buffer, sizeof(buffer));

        if (nbytes < 0)
        {
            perror("Failed to read from tun interface");
            return 1;
        }

        uint16_t protocol = (buffer[2] << 8) | buffer[3];

        if (protocol != 0x800) {
            // Ignoring ip packets other than an IPV4
            continue;
        }

        Ipv4Header *ipHeader = (Ipv4Header *)(buffer + 4);
        std::cout << std::hex << "Ipv4 packet protocol: " << (ipHeader->protocol << 8) << std::endl;
    }

    close(tun_fd);
    return 0;
}   