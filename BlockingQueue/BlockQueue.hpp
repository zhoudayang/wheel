#ifndef BLOCKING_QUEUE
#define BLOCKING_QUEUE

#include <mutex>
#include <condition_variable>
#include <deque>

#include <boost/noncopyable.hpp>
#include <assert.h>

using std::mutex;
using std::condition_variable;
using std::deque;
using std::unique_lock;

template<typename T>
class BlockingQueue : boost::noncopyable {
public:
    BlockingQueue() {}

    void put(const T &x) {
        unique_lock<mutex> lock(mutex_);
        queue_.push_back(x);
        notEmpty_.notify_one();
    }

    //右值引用版本，移动语义
    void put(T &&x) {
        unique_lock<mutex> lock(mutex_);
        queue_.push_back(std::move(x));
        notEmpty_.notify_one();
    }

    T take() {
        unique_lock<mutex> lock(mutex_);
        while (queue_.empty()) {
            notEmpty_.wait(lock);
        }
        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        return front;
    }

    size_t size() const {
        unique_lock<mutex> lock(mutex_);
        return queue_.size();
    }

private:
    mutable mutex mutex_;
    condition_variable notEmpty_;
    deque<T> queue_;

};

#endif