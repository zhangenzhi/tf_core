#include <iostream>
#include <stdlib.h>
#include <functional>
#include "test.h"

typedef std::uint64_t uint64;

int main()
{
    std::cout << "Hello Geek\n";
    std::function<uint64()>* p;
    helloWorld();
    return 0;
}