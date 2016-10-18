#pragma once



namespace zy
{
	class Condition;

	class Mutex
	{
	public:
		Mutex();

		~Mutex();

		void lock();

		void unlock();

		void assertHeld();

	private:

		friend class Condition;

		// critical sections are more efficient than mutexes
		// but they are not recursive and can only be used to synchronize threads within the same process
		// we use opaque void * to avoid including windows.h in Mutex.h
		void *mutex_;

		//No copying
		Mutex(const Mutex &);
		void operator=(const Mutex &);

	};

	class MutexLockGuard
	{
	public:

		explicit MutexLockGuard(Mutex &mutex) :
			mutex_(mutex)
		{
			mutex_.lock();
		}

		~MutexLockGuard()
		{
			mutex_.unlock();
		}

	private:
		Mutex &mutex_;
	};

	class Condition
	{
	public:

		explicit Condition(Mutex *mu);

		~Condition();

		void wait();

		void signal();

		void signalAll();

	private:

		Mutex * mu_;
		Mutex wait_mtx_;
		long waiting_;
		void * sema_;
		void * event_;

		bool broadcasted_;
	};


}