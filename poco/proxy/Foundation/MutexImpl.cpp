#include "Mutex.h"
#include "Poco/Mutex.h"

namespace base
{

    Mutex::Mutex()
    {
        proxy = new Poco::Mutex;
    }
		
    Mutex::~Mutex()
    {
        delete proxy;
    }

	void Mutex::lock()
    {
        proxy->lock();
    }
		
	void Mutex::lock(long milliseconds)
    {
        proxy->lock(milliseconds);
    }

	bool Mutex::tryLock()
    {
        return proxy->tryLock();
    }

	bool Mutex::tryLock(long milliseconds)
    {
        return proxy->tryLock(milliseconds);
    }

	void Mutex::unlock()
    {
        proxy->unlock();
    }


    FastMutex::FastMutex()
    {
        proxy = new Poco::FastMutex;
    }
		
    FastMutex::~FastMutex()
    {
        delete proxy;
    }

	void FastMutex::lock()
    {
        proxy->lock();
    }

	void FastMutex::lock(long milliseconds)
    {
        proxy->lock(milliseconds);
    }

	bool FastMutex::tryLock()
    {
        return proxy->tryLock();
    }

	bool FastMutex::tryLock(long milliseconds)
    {
        return proxy->tryLock(milliseconds);
    }

	void FastMutex::unlock()
    {
        proxy->unlock();
    }
	
}
