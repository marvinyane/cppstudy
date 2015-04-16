#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <vector>
#include <string>
#include <tr1/memory>

#include "types.h"

#include "RingBuffer.h"

namespace Poco{
    namespace Net{
        class Socket;
        class StreamSocket;
        class ServerSocket;
        class MulticastSocket;
    }
}


namespace base{
    class SocketHandler;
namespace Net{

    class IPAddress;
    class SocketAddress;
    class StreamSocket;
    class ServerSocket;
    class NetworkInterface;

    class Socket
    {
        public:
            typedef std::vector<Socket*> SocketList;

            Socket(base::SocketHandler* handler);
            ~Socket();

            static int select(SocketList& readList, SocketList& writeList,
                    SocketList& exceptList, const int timeout);

            virtual void close() = 0;
            virtual Poco::Net::Socket* getProxy() = 0;
            virtual SocketAddress getAddress() = 0;
            virtual void setBlocking(bool) = 0;

            virtual void readEvent() = 0;
            virtual void writeEvent() = 0;
            virtual void exceptEvent() = 0;

            // socketNode read and write
            int read(char* buffer, int length);
            int write(const char* buffer, int length);

        protected:
            char* readToSend(int& length);
            void SendFailed(char* buffer, int length, int sign);
            int writeFromRead(const char* buffer, int length);
            base::SocketHandler* m_handler;

        private:
            Socket(const Socket& socket);
            Socket& operator=(const Socket&);

            base::RingBuffer m_read;
            base::RingBuffer m_write;
            char* m_readLeft;
            int   m_readSign;
            int   m_readLen;
            char* m_writeLeft;
            int   m_writeSign;
            int   m_writeLen;

    };

    class StreamSocket : public Socket
    {
        public:
            StreamSocket(SocketHandler* handler);
            StreamSocket(const StreamSocket&);
            StreamSocket(Poco::Net::StreamSocket& socket, SocketHandler* handler);
            ~StreamSocket();

            StreamSocket& operator= (const StreamSocket&);

            int connect(const SocketAddress& address);
            int connect(const SocketAddress& address, const int timeout);
            int connectNB(const SocketAddress& address);
            void shutdown();

            virtual void close();
            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);

            virtual void readEvent();
            virtual void writeEvent();
            virtual void exceptEvent();

        private:
            std::tr1::shared_ptr<Poco::Net::StreamSocket> proxy;
    };

    class ServerSocket : public Socket
    {
        public:
            ServerSocket(SocketHandler* handler);
            ServerSocket(const ServerSocket&);
            ~ServerSocket();

            ServerSocket& operator=(const ServerSocket&);

            void bind(SocketAddress& addr, bool reuse);
            void bind(UInt16 port);
            void listen();
            std::tr1::shared_ptr<StreamSocket> acceptConnection();

            virtual void close();
            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);
            
            virtual void readEvent();
            virtual void writeEvent();
            virtual void exceptEvent();

        private:
            std::tr1::shared_ptr<Poco::Net::ServerSocket> proxy;
    };


    class MulticastSocket : public Socket
    {
        public:
            MulticastSocket(SocketHandler* handler);
            MulticastSocket(const MulticastSocket&);
            MulticastSocket(const Poco::Net::MulticastSocket&, SocketHandler*);
            ~MulticastSocket();

            MulticastSocket& operator=(const MulticastSocket&);

            void bind(SocketAddress& addr, bool reuse);
            void setInterface(const NetworkInterface&);
            void setLoopback(bool);
            void joinGroup(const IPAddress& groupAddress, const NetworkInterface& interfc);

            virtual void close();
            virtual Poco::Net::Socket* getProxy();
            virtual SocketAddress getAddress();
            virtual void setBlocking(bool);
            
            virtual void readEvent();
            virtual void writeEvent();
            virtual void exceptEvent();
            
        private:
            std::tr1::shared_ptr<Poco::Net::MulticastSocket> proxy;
    };
}} // namespace

#endif
