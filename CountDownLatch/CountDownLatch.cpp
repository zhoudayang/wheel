//
// Created by zhouyang on 16-7-30.
//

#include "CountDownLatch.h"
using std::mutex;
using std::unique_lock;

CountDownLatch::CountDownLatch(int count) : count_(count) {}

void CountDownLatch::wait() {
    unique_lock<mutex> lock(mutex_);
    while (count_ > 0) {
        condition_.wait(lock);
    }
}

void CountDownLatch::countDown() {
    unique_lock<mutex> lock(mutex_);
    --count_;
    if (count_ == 0) {
        condition_.notify_all();
    }
}

int CountDownLatch::getCount() const {
    unique_lock<mutex> lock(mutex_);
    return count_;
}
