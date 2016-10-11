#include <condition_variable>
#include <mutex>
#include <thread>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <deque>

using std::thread;
using std::condition_variable;
using std::mutex;

class ThreadPool :boost::noncopyable {
public:
	typedef boost::function<void()> Task;
	explicit ThreadPool();

	~ThreadPool();

	//set max queue size 
	void setMaxQueueSize(int maxSize) {
		maxQueueSize_ = maxSize;
	}

	//start to run,set thread num to numThreads
	void start(int numThreads);

	//stop threadPool
	void stop();

	//return queue size 
	size_t queueSize() const;

	//run the function f
	void run(const Task &&f);

	//run the function f 
	void run(const Task &f);

private:
	//if queue full ? 
	bool isFull() const;

	//main function run in the thread 
	void runInThread();

	//take function from queue 
	Task take();

	mutable mutex mutex_;
	condition_variable notEmpty_;
	condition_variable notFull_;
	Task threadInitCallback_;
	boost::ptr_vector<thread> threads_;
	std::deque<Task> queue_;
	size_t maxQueueSize_;
	//if running is false,唤醒take函数，他将立即返回
	bool running_;

};
