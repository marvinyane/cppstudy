#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#include <string>
#include <tr1/memory>
#include <vector>

namespace base
{
namespace Net
{
    class SocketAddress;
    class Socket;
    class StreamSocket;
}
class WorkThread;

class SocketHandler
{
    public:
        virtual void connected(Net::StreamSocket* socket)=0;
        virtual void readReady(Net::Socket* socket)=0;
        virtual void disconnected(Net::Socket* socket)=0;
        virtual WorkThread* getWorkThread() = 0;
};


class SocketNode
{
    public:
        SocketNode(std::tr1::shared_ptr<Net::Socket> socket);
        SocketNode(const SocketNode&);
        ~SocketNode();

        SocketNode& operator=(const SocketNode&);

        int read(char* buffer, int length);
        int write(const char* buffer, int length);
        void close();
        int readAvalible();

        Net::Socket* getSocket();

    private:
        std::tr1::shared_ptr<Net::Socket> m_socket;

};


class IOManager
{
    public:
        IOManager();
        ~IOManager();

        SocketNode* addServerSocket(Net::SocketAddress& addr, SocketHandler *handler);
        //SocketNode* addServerSocket(UInt16 port, SocketHandler *handler);

        SocketNode* addClientSocket(Net::SocketAddress &addr, SocketHandler *handler);

        SocketNode* addMulticastSocket(Net::SocketAddress& addr, SocketHandler *handler);

        bool removeSocket(SocketNode* node);



    private:
        bool m_running;
        WorkThread* m_thread;
        void run(void);
        std::vector<SocketNode*> m_sockets;

        void addSocketNode(SocketNode* node);
        void removeSocketNode(SocketNode* node);
};

}
#endif
