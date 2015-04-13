#include "buffer.h"

#include <iostream>
#include <cstdio>

using namespace MirrorLink;

int main()
{
    Buffer<char>  b(0);

    b.resize(10);
    b.assign("hello", 5);

    std::string s;

    s.assign(b.begin());

    typedef const char* (Buffer<char>::*P)()const;
    typedef char* (Buffer<char>::*Q)();

    P p = &MirrorLink::Buffer<char>::begin;
    Q q = &MirrorLink::Buffer<char>::begin;

    printf("%p- %p\n", q, p);
    


    return 0;
}



