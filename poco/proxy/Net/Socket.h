#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <vector>
#include <string>
#include <tr1/memory>

#include "types.h"

namespace Poco{
    namespace Net{
        class Socket;
        class StreamSocket;
        class ServerSocket;
        class MulticastSocket;
    }
}


namespace base{
namespace Net{

    class IPAddress;
    class SocketAddress;
    class StreamSocket;
    class NetworkInterface;

    class Socket
    {
        public:
            Socket();
            virtual ~Socket();
            typedef std::vector<Socket*> SocketList;

            virtual void close() = 0;

            virtual StreamSocket* acceptConnection();
            virtual int sendBytes(const char* buffer, int length);
            virtual int receiveBytes(char* buffer, int length);

            static int select(SocketList& readList, SocketList& writeList,
                    SocketList& exceptList, const int timeout);

            virtual Poco::Net::Socket* getProxy() = 0;
            virtual SocketAddress getAddress() = 0;
            virtual void setBlocking(bool);

        private:
            Socket(const Socket& socket);
            Socket& operator=(const Socket&);


    };

    class StreamSocket : public Socket
    {
        public:
            StreamSocket();
            StreamSocket(Poco::Net::StreamSocket* socket);
            ~StreamSocket();

            StreamSocket& operator= (const StreamSocket&);

            int connect(const SocketAddress& address);
            int connect(const SocketAddress& address, const int timeout);
            int connectNB(const SocketAddress& address);

            virtual void close();

            virtual int sendBytes(const char* buffer, int length);
            virtual int receiveBytes(char* buffer, int length);
            void shutdown();

            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);
        private:
            Poco::Net::StreamSocket* proxy;
    };

    class ServerSocket : public Socket
    {
        public:
            ServerSocket();
            ~ServerSocket();

            void bind(SocketAddress& addr, bool reuse);
            void bind(UInt16 port);
            void listen();

            virtual void close();
            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);

            virtual StreamSocket* acceptConnection();
        private:
            Poco::Net::ServerSocket* proxy;
    };


    class MulticastSocket : public Socket
    {
        public:
            MulticastSocket();
            MulticastSocket(const MulticastSocket&);
            MulticastSocket(const Poco::Net::MulticastSocket&);
            ~MulticastSocket();

            MulticastSocket& operator=(const MulticastSocket&);

            virtual void close();
            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);
            void bind(SocketAddress& addr, bool reuse);

            void setInterface(const NetworkInterface&);
            void setLoopback(bool);
            void joinGroup(const IPAddress& groupAddress, const NetworkInterface& interfc);
            
            virtual int sendBytes(const char* buffer, int length);
            virtual int receiveBytes(char* buffer, int length);

        private:
            std::tr1::shared_ptr<Poco::Net::MulticastSocket> proxy;

    };

}

}


#endif
