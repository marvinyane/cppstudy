#ifndef __IOMANAGER_H__
#define __IOMANAGER_H__

#include "../Foundation/RingBuffer.h"
#include "../Foundation/WorkThread.h"

#include "Poco/Net/Socket.h"

#include <string>

namespace base
{

class WorkThread;

class SocketHandler
{
    public:
        SocketHandler(){}
        SocketHandler(base::WorkThread *work) : m_work(work)
        {
            m_work->start();
        }

        virtual ~SocketHandler()
        {
            if (m_work)
            {
                m_work->stop();
                m_work->wait(3000);
            }
        }

        virtual void readReady(Poco::Net::Socket& socket)
        {
        }

        void setWorkThread(base::WorkThread* work)
        {
            m_work = work;
            m_work->start();
        }
        base::WorkThread* getWorkThread()
        {
            return m_work;
        }
    private:
        base::WorkThread *m_work;

};


class IOManager
{
    public:
        IOManager();
        ~IOManager();

        bool addSocket(Poco::Net::Socket &socket, SocketHandler *handler);

        int readSocket(Poco::Net::Socket &socket, char* s, int length);

        int writeSocket(Poco::Net::Socket &socket, const char* s, int length);

        int readSocketAvalible(Poco::Net::Socket &socket);

        void run(void);

    private:
        bool m_running;
        WorkThread* m_thread;
        struct SocketNode
        {
            public:
                Poco::Net::Socket m_socket;
                base::SocketHandler* m_handler;
                base::RingBuffer m_read;
                base::RingBuffer m_write;

                SocketNode(Poco::Net::Socket &socket, SocketHandler *handler) :
                    m_socket(socket),
                    m_handler(handler),
                    m_read(),
                    m_write()
                {
                }
        };

        std::vector<SocketNode*> m_sockets;

        /*add - delete - search*/
        void addSocketNode(Poco::Net::Socket& socket, base::SocketHandler* handler);
        void deleteSocketNode(Poco::Net::Socket& socket);
        SocketNode* searchSocketNode(Poco::Net::Socket& socket);
};

}
#endif
