#include <iostream>

namespace test{

void helloWorld()
{
    std::cout << "Hello World\n";
}

class TestClass
{
    public:
        std::string PrintString() const;
        void PrintVoid() const;
};      

}//test