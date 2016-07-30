#include <thread>
#include <stdio.h>
#include "BoundedBlockingQueue.hpp"

using std::thread;

BoundedBlockingQueue <int> queue(10);


void producer(){
    while(true){
        for(int i=0;i<10;i++){
            queue.put(i);
            printf("enqueue %d\n",i);
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
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}