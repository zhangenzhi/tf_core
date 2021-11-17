#include <iostream>
#include <stdlib.h>
#include <functional>
#include "allocator.h"
#include "test.h"
#include "types.h"

#include <mutex>
#include <thread>
using namespace std;
mutex mtx;

void print_block(int n,char c ){
    mtx.lock();
    for (int i=0;i<n;i++){cout<<c;}
    cout<<'\n';
    mtx.unlock();
}

int main()
{
    thread th1(print_block,50,'*');
    thread th2(print_block,50,'-');

    th1.join();
    th2.join();

    return 0;
}