#include <iostream>
#include <stdlib.h>
#include <functional>
#include "allocator.h"
#include "test.h"
#include "types.h"

#define PREDICT_FALSE(x) (x)

int main()
{
    std::cout << "Hello Geek\n";
    std::function<tfcore::uint64()>* p;

    tfcore::AllocationAttributes(false,false,p);
    tfcore::AllocatorStats();

    // tfcore::Allocator();
    std::cout << PREDICT_FALSE(10)<<std::endl;
    helloWorld();

    int i = 3;
    int j = 3;

    i = i | 5;
    std::cout << i <<std::endl;
    j |= 5;
    std::cout << j <<std::endl;

    return 0;
}