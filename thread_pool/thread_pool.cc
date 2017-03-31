#include "thread_pool.h"
#include <boost/bind.hpp>
#include <assert.h>
#include <mutex>
#include <stdio.h>
#include <exception>


using std::unique_lock;
/* maxQueueSize set the max size of waiting list, if set it as zero, means the max size is unlimited */
ThreadPool::ThreadPool() :
	mutex_(),
	notEmpty_(),
	notFull_(),
	maxQueueSize_(0),
	running_(false)
{
}

//stop all thread
ThreadPool::~ThreadPool()
{
	if (running_)
		stop();
}

void ThreadPool::start(int numThreads)
{
	assert(threads_.empty());
	running_ = true;
	threads_.reserve(numThreads);
	for (int i = 0; i < numThreads; i++) {
		threads_.push_back(new thread(std::bind(&ThreadPool::runInThread, this)));
	}
	if (numThreads == 0 && threadInitCallback_)
		threadInitCallback_();
}
void ThreadPool::stop()
{

	{
		unique_lock<mutex> lock(mutex_);
    // set running_ to false
		running_ = false;
		notEmpty_.notify_all();
	}

	for_each(threads_.begin(), threads_.end(), [](thread &t) {
		t.join();
	});
}

size_t ThreadPool::queueSize() const
{
	unique_lock<mutex> lock(mutex_);
	return queue_.size();
}

// if thread pool size is not empty, put task into queue_
void ThreadPool::run(const Task && task)
{
	if (threads_.empty()) {
		task();
	}
	else {
		unique_lock<mutex> lock(mutex_);
		while (isFull()) {
			notFull_.wait(lock);
		}
		assert(!isFull());
		queue_.push_back(std::move(task));
		notEmpty_.notify_one();
	}
}

void ThreadPool::run(const Task & task)
{
	if (threads_.empty()) {
		task();
	}
	else {
		unique_lock<mutex> lock(mutex_);
		while (isFull()) {
			notFull_.wait(lock);
		}
		assert(!isFull());
		queue_.push_back(task);
		notEmpty_.notify_one();
	}
}

bool ThreadPool::isFull() const
{
	assert(!mutex_.try_lock());
	return maxQueueSize_ > 0 && queue_.size() >= maxQueueSize_;
}

void ThreadPool::runInThread()
{
	try {
		if (threadInitCallback_) {
			threadInitCallback_();
		}
    // if not running_ now, will not execute the task, just exit silently
		while (running_) {
			Task task(take());
			//if task is valid, run it
			if (task) {
				task();
			}
		}
	}
	catch (const std::exception &ex) {
		fprintf(stderr, "exception caught in ThreadPool \n");
		fprintf(stderr, "reason %s\n", ex.what());
		abort();
	}
}

ThreadPool::Task ThreadPool::take()
{
	unique_lock<mutex> lock(mutex_);
	// if not running and queue_ is empty return invalid Task instance
	while (queue_.empty() && running_) {
		notEmpty_.wait(lock);
	}
	Task task;
	if (!queue_.empty()) {
		task = queue_.front();
		queue_.pop_front();
		if (maxQueueSize_ > 0)
			notFull_.notify_one();
	}
	return task;
}

