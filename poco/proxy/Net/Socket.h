#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <vector>

namespace Poco{
    namespace Net{
        class Socket;
        class StreamSocket;
    }
}


namespace base{
namespace Net{

    class SocketAddress;

    class Socket
    {
        public:
            Socket();
            virtual ~Socket();
            typedef std::vector<Socket*> SocketList;

            virtual void close() = 0;

            virtual int sendBytes(const char* buffer, int length);
            virtual int receiveBytes(char* buffer, int length);

            static int select(SocketList& readList, SocketList& writeList,
                    SocketList& exceptList, const int timeout);

            virtual Poco::Net::Socket* getPorxy() = 0;

            virtual SocketAddress getAddress() = 0;

        private:
            Socket(const Socket& socket);
            Socket& operator=(const Socket&);


    };

    class StreamSocket : public Socket
    {
        public:
            StreamSocket();
            ~StreamSocket();

            StreamSocket& operator= (const StreamSocket&);

            int connect(const SocketAddress& address);
            int connect(const SocketAddress& address, const int timeout);
            int connectNB(const SocketAddress& address);

            virtual void close();

            virtual int sendBytes(const char* buffer, int length);
            virtual int receiveBytes(char* buffer, int length);
            void shutdown();

            virtual Poco::Net::Socket* getPorxy();
            virtual SocketAddress getAddress();
        private:
            Poco::Net::StreamSocket* proxy;
    };

}

}


#endif
