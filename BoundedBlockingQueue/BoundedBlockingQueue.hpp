#ifndef BOUNDED_BLOCKING_QUEUE
#define BOUNDED_BLOCKING_QUEUE

#include <mutex>
#include <condition_variable>

#include <boost/circular_buffer.hpp>
#include <boost/noncopyable.hpp>
#include <assert.h>

using std::mutex;
using std::condition_variable;
using std::unique_lock;

//有界阻塞队列
template<typename T>
class BoundedBlockingQueue : boost::noncopyable {
public:
    explicit BoundedBlockingQueue(int maxSize) : queue_(maxSize) {

    }

    void put(const T &x) {
        unique_lock<mutex> lock(mutex_);
        while (queue_.full()) {// wait for position to hold x
            notFull_.wait(lock);
        }
        assert(!queue_.full());
        queue_.push_back(x);
        notEmpty_.notify_one();// now is not empty
    }

    T take() {
        unique_lock<mutex> lock(mutex_);
        while (queue_.empty()) {// wait for one to take
            notEmpty_.wait(lock);
        }
        assert(!queue_.empty());
        T front(queue_.front());
        queue_.pop_front();
        notFull_.notify_one();// now is not full
        return front;
    }

    bool empty() const {// is empty?
        unique_lock<mutex> lock(mutex_);
        return queue_.empty();
    }

    bool full() const {//  is full?
        unique_lock<mutex> lock(mutex_);
        return queue_.full();
    }

    size_t size() const {// return size
        unique_lock<mutex> lock(mutex_);
        return queue_.size();
    }

    size_t capacity() const {// return capacity
        unique_lock<mutex> lock(mutex_);
        return queue_.capacity();
    }

private:
    mutable mutex mutex_;
    condition_variable notEmpty_;
    condition_variable notFull_;
    //use boost::circular_buffer to hold T
    boost::circular_buffer<T> queue_;
};


#endif