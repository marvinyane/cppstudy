#ifndef __NETWORKINTERFACE_H__
#define __NETWORKINTERFACE_H__

#include <tr1/memory>
#include <string>
#include <vector>

//#include "SocketAddress.h"

namespace Poco
{
    namespace Net
    {
        class NetworkInterface;
    }
}

namespace base{
namespace Net{

    class IPAddress;

    class NetworkInterface
    {
        public:
            typedef std::vector<NetworkInterface> NetworkInterfaceList;

            NetworkInterface();
            NetworkInterface(const NetworkInterface&);
            NetworkInterface(Poco::Net::NetworkInterface&);
            NetworkInterface& operator=(const NetworkInterface&);
            ~NetworkInterface();

            static NetworkInterfaceList list();
            static NetworkInterface forIndex(int index);

            const IPAddress& address();
            const std::string& name();

        private:
            std::tr1::shared_ptr<Poco::Net::NetworkInterface> proxy;
            IPAddress*   addr;
    };




}} //namespace

#endif
