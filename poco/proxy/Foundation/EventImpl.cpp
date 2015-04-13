#include "Event.h"
#include "Poco/Event.h"

#include <iostream>
#include <typeinfo>

namespace base
{

    Event::Event(bool autoReset)
    {
        proxy = new Poco::Event(autoReset);
    }
		
    Event::~Event()
    {
        delete proxy;
    }

	void Event::set()
    {
        proxy->set();
    }

	void Event::wait()
    {
        proxy->wait();
    }

	void Event::wait(long milliseconds)
    {
        try
        {
            proxy->wait(milliseconds);
        }
        catch(Poco::SystemException e)
        {
        }
        catch(Poco::TimeoutException e)
        {
        }
    }

	bool Event::tryWait(long milliseconds)
    {
        return proxy->tryWait(milliseconds);
    }

	void Event::reset()
    {
        proxy->reset();
    }
	
}
