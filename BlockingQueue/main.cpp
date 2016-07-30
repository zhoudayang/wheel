#include <stdio.h>
#include <thread>
#include "BlockQueue.hpp"

using std::thread;

BlockingQueue <int> queue;


void producer(){
    while(true){
        for(int i=0;i<10;i++){
            queue.put(i);
            printf("enqueue %d \n",i);
        }
    }
}

void consumer(){
    while(true){
        printf("dequeue %d\n",queue.take());
    }
}


int main(){
    thread producerThread(producer);
    thread consumerThread1(consumer);
    thread consumerThread2(consumer);
    producerThread.join();
    consumerThread1.join();
    consumerThread2.join();
}
