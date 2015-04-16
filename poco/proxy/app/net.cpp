#include "IOManager.h"
#include "WorkThread.h"

#include "NetworkInterface.h"
#include "Socket.h"
#include "SocketAddress.h"

#include <iostream>
#include <cstring>

bool running = true;

// TODO
class MyHandler : public base::SocketHandler
{
    public:
        MyHandler() :
            m_io(new base::IOManager)
        {
            m_work = new base::WorkThread;
            m_work->start();
        }
        ~MyHandler()
        {
            /*close socket?*/
            delete m_io;
            delete m_work;
        }

        void connect()
        {
            base::Net::SocketAddress addr("127.0.0.1:6666");
            node = m_io->addClientSocket(addr, this);

            if (node)
            {
                node->write("hello", 6);
            }
            else
            {
            }
        }


        void connected(base::Net::StreamSocket* socket)
        {
            std::cout << "connected!\n";
        }

        void readReady(base::Net::Socket* socket)
        {
            std::cout << "readReady!\n";
        }

        void disconnected(base::Net::Socket* socket)
        {
            std::cout << "disconnected!\n";
        }

        base::WorkThread* getWorkThread()
        {
            return m_work;
        }

    private:
        base::WorkThread* m_work;
        base::IOManager* m_io;
        base::SocketNode* node;
};

int main()
{

    MyHandler handler;
    handler.connect();

    while (running)
    {
        sleep (1);
    }

    return 0;
}
