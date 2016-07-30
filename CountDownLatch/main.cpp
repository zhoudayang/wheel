
#include "CountDownLatch.h"
#include <stdio.h>
#include <unistd.h>
#include <thread>

using std::thread;

// global CountDownLatch variable
CountDownLatch count(2);

void worker1(){
    printf("worker 1 begin to work\n");
    sleep(2);
    count.countDown();
    printf("worker 1 complete work\n");
}

void worker2(){
    printf("worker 2 begin to work\n");
    sleep(2);
    count.countDown();
    printf("worker 2 complete work\n");
}

void boss(){
    count.wait();
    printf("workers complete their works, now I need to check!\n");
}

int main() {
    thread thread1(worker1);
    thread thread2(worker2);
    thread thread3(boss);

    thread1.join();
    thread2.join();
    thread3.join();
}