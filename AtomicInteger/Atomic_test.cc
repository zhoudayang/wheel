#include "Atomic.hpp"
#include <iostream>
#include <thread>
#include <assert.h>

using std::cout;
using std::endl;

detail::AtomicInt32 integer;

void threadFunc1()
{
  for (int i = 0; i < 1000000; i++)
  {
    integer.increment();
  }
}

void threadFunc2()
{
  for (int i = 0; i < 1000000; i++)
  {
    integer.decrement();
  }
}

int main()
{
  std::thread t1(threadFunc1);
  std::thread t2(threadFunc2);

  t1.join();
  t2.join();

  assert(integer.get() == 0);

}