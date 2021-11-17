#include <iostream>
#include <stdlib.h>
#include <functional>
// #include "allocator.h"
// #include "test.h"
// #include "types.h"

#include <mutex>
#include <thread>
using namespace std;
mutex mtx;

void print_block(int n, char c ){
    // mtx.lock();
    for (int i=0;i<n;i++){cout<<c;}
    cout<<'\n';
    // mtx.unlock();
}
void print_even(int x){
    if (x%2==0){cout<< x<< "is even \n";}
    else throw (logic_error("not even"));

}
void print_thread_id(int id){
    try{
        // std::lock_guard<mutex> lck (mtx);
        print_even(id);
    }
    catch(logic_error&){
        cout<<"[exception caught]\n";
    }
}
int main()
{
    // std::thread th1(print_block,50,'*');
    // std::thread th2(print_block,50,'-');

    // th1.join();
    // th2.join();

    thread threads[10];
    for(int i=0; i<10;i++)
        threads[i] = thread(print_thread_id, i+1);
    for (auto& th : threads) th.join();

    return 0;
}