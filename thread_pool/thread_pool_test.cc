#include "thread_pool.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void thread_func()
{
  printf("begin!\n");
  sleep(1);
  printf("end now\n");
}

int main()
{

  ThreadPool pool;
  pool.start(5);
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));
  pool.run(std::bind(&thread_func));

  pool.stop();


  return 0;
}
