#include <iostream>
#include "Mutex.h"
#include <thread>


//CountDownLatch, when count_ equal to zero signal one thread
class CountDownLatch
{
public:
	explicit CountDownLatch(int count) :
		mutex_(),
		condition_(&mutex_),
		count_(count)
	{

	}

	void wait()
	{
		zy::MutexLockGuard lock(mutex_);
		while (count_ > 0)
		{
			condition_.wait();
		}
	}

	void countDown()
	{
		zy::MutexLockGuard lock(mutex_);
		--count_;
		if (count_ == 0)
			condition_.signal();
	}

	int getCount() const
	{
		zy::MutexLockGuard lock(mutex_);
		return count_;
	}

private:
	mutable zy::Mutex mutex_;
	zy::Condition condition_;
	int count_;
};


void worker(CountDownLatch & latch)
{

	std::this_thread::sleep_for(std::chrono::seconds(1));
	printf("work complete!\n");
	latch.countDown();
}

void boss(CountDownLatch & latch)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	latch.wait();
	printf("workers complete the work! now I need to check it\n");
}


//CountDownLatch_2, when count_ equal to zero signal all threads
class CountDownLatch_2
{
public:
	explicit CountDownLatch_2(int count) :
		mutex_(),
		condition_(&mutex_),
		count_(count)
	{

	}

	void wait()
	{
		zy::MutexLockGuard lock(mutex_);
		while (count_ > 0)
		{
			condition_.wait();
		}
	}

	void countDown()
	{
		zy::MutexLockGuard lock(mutex_);
		--count_;
		if (count_ == 0)
			condition_.signalAll();
	}

	int getCount() const
	{
		zy::MutexLockGuard lock(mutex_);
		return count_;
	}

private:
	mutable zy::Mutex mutex_;
	zy::Condition condition_;
	int count_;
};

void cooker(CountDownLatch_2 & latch)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	printf("I am complete! come here, waiters!\n");
	latch.countDown();
}

void waiters(CountDownLatch_2 & latch)
{
	latch.wait();
	printf("cooker complete! I can work now!\n");
}

using std::thread;

int main()
{

	CountDownLatch latch(2);

	//thread传入参数时如果传入的是引用，必须使用std::ref
	thread t1(boss, std::ref(latch));
	thread t2(worker, std::ref(latch));
	thread t3(worker, std::ref(latch));

	t2.detach();
	t3.detach();

	t1.join();

	CountDownLatch_2 latch2(1);
	thread t4(waiters, std::ref(latch2));
	thread t5(waiters, std::ref(latch2));
	thread t6(cooker, std::ref(latch2));

	t6.detach();
	t4.join();
	t5.join();


	return 0;
}