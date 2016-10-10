#include "tmp.h"

extern int getValue();

int main()
{
    int a = getValue();
    if (a == TEST_A)
    {
        return 0;
    }

    return 1;
}
