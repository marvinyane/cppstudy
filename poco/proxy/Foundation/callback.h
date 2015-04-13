#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include <tr1/functional>

typedef std::tr1::function<void(void)> Closure;

#define Bind std::tr1::bind


#endif
