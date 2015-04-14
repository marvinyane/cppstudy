#include "IOManager.h"
#include "../Foundation/WorkThread.h"

#include <iostream>
#include <cstring>


class MyHandler : public base::SocketHandler
{
    public:
        MyHandler(base::WorkThread* work, base::IOManager* manager) : 
            SocketHandler(work),
            m_io(manager)
        {
        }

        void readReady(base::Net::Socket* socket)
        {
            char buffer[1000];
            memset(buffer, 0, sizeof(buffer));
            int len = m_io->readSocket(socket, buffer, sizeof(buffer));

            std::cout << buffer << " size is : " << len << std::endl;
        }

    private:
        base::IOManager* m_io;
        
};

int main()
{
    base::IOManager m;
    base::WorkThread w("my_workThread");

    MyHandler *handler = new MyHandler(&w, &m);

    base::Net::SocketAddress addr("localhost", 6666);

    base::Net::StreamSocket *socket = new base::Net::StreamSocket; 

    if (socket->connect(addr) != 0)
    {
        std::cout << "connect failed!\n";
    }

    m.addSocket(socket, handler);

    while (1)
    {
        char* s = new char[20];
        memcpy(s, "hello world", 12);
        m.writeSocket(socket, s, 12);
        sleep (1);
    }
    return 0;
}
