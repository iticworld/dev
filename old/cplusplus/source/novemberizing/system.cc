/**
 *
 * @author      novemberizing <novemberizing@gmail.com>
 * @since       0.0.1
 * @date        2018. 6. 19.
 */

#include <unistd.h>
#include <string.h>

#ifndef   WIN32
#include <linux/if.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#endif // WIN32

#include "novemberizing.hh"
#include "novemberizing/exception.hh"

namespace novemberizing
{
    int32 system::sleep(int64 unisecond)
    {
#ifndef   WIN32
        return usleep((__useconds_t) unisecond);
#else  // WIN32
        throw exception();
#endif // WIN32
    }

//    bytes system::mac()
//    {
//        struct ifreq ifr;
//        struct ifconf ifc;
//        char buf[1024];
//        int success = 0;
//
//        int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
//        if (sock == -1) { /* handle error*/ };
//
//        ifc.ifc_len = sizeof(buf);
//        ifc.ifc_buf = buf;
//        if (ioctl(sock, SIOCGIFCONF, &ifc) == -1)
//        {
//            throw exception();
//        }
//
//        struct ifreq* it = ifc.ifc_req;
//        const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));
//
//        for (; it != end; ++it)
//        {
//            strcpy(ifr.ifr_name, it->ifr_name);
//            if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0)
//            {
//                if (! (ifr.ifr_flags & IFF_LOOPBACK))
//                {
//                    if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0)
//                    {
//                        bytes out;
//                        for (int i = 0; i < 6; ++i)
//                        {
//                            out += ifr.ifr_addr.sa_data[i];
//                        }
//                        return out;
//                    }
//                }
//            }
//            else
//            {
//                throw exception();
//            }
//        }
//        return bytes();
//    }
}

