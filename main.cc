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

    // tfcore::AllocationAttributes(false,false,p);
    tfcore::AllocatorStats* as;
    std::string s = as->DebugString();
    

    // tfcore::Allocator *a;
    // std::cout << PREDICT_FALSE(10)<<std::endl;
    tfcore::helloWorld();
    tfcore::TestClass* t;
    t->HelloConst();

    // bool v = false;
    // std::cout<<(v & 0x1)<<std::endl;
    // std::cout<<(0x1 << 1)<<std::endl;
    // std::cout<<(0x1 << 2)<<std::endl;
    // std::cout<<(v & (0x1 << 2))<<std::endl;
    return 0;
}