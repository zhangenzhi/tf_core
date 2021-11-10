#include <iostream>

namespace tfcore{

void helloWorld();

class TestClass
{
    public:
        std::string PrintString() const;
        void PrintVoid() const;
        void HelloConst();
};      

}//test