#include "Atomic.hpp"
#include <iostream>
#include <thread>

using namespace std;

detail::AtomicInt32 integer;

void threadFunc1(){
    for(int i=0;i<10;i++)
        integer.increment();
}

void threadFunc2(){
    for(int i=0;i<10;i++)
        integer.decrement();
}

int main() {
    thread thread1(threadFunc1);
    thread thread2(threadFunc2);

    thread1.join();
    thread2.join();

    cout<<"the integer now is "<<integer.get()<<endl;


}