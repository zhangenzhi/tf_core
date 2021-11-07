#include <iostream>
#include <stdlib.h>
#include <functional>
#include "allocator.h"
#include "test.h"
#include "types.h"


int main()
{
    std::cout << "Hello Geek\n";
    std::function<tfcore::uint64()>* p;

    tfcore::AllocationAttributes(false,false,p);
    tfcore::AllocatorStats;
    helloWorld();
    return 0;
}