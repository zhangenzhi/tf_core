#include "test.h"


namespace tfcore{

    std::string TestClass::PrintString() const{
        std::string s = "Print String!\n";
        return s;
    }

    void TestClass::PrintVoid() const{
        std::cout<< "void."<<std::endl;
    }

}