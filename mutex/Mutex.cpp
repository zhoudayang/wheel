
#include "Mutex.h"

#include <Windows.h>
#include <cassert>

namespace zy
{
	Mutex::Mutex() :
		mutex_(::CreateMutex(NULL, false, NULL))
	{
		assert(mutex_);
	}

	Mutex::~Mutex()
	{
		assert(mutex_);
		::CloseHandle(mutex_);
	}

	void Mutex::lock()
	{
		assert(mutex_);
		WaitForSingleObject(mutex_, INFINITE);
	}

	void Mutex::unlock()
	{
		assert(mutex_);
		::ReleaseMutex(mutex_);
	}

	void Mutex::assertHeld()
	{
		assert(mutex_);
		assert(1);
	}


	Condition::Condition(Mutex* mu)
		:waiting_(0),
		mu_(mu),
		sema_(::CreateSemaphore(NULL, 0, 0x7fffffff, NULL)),
		event_(::CreateEvent(NULL, FALSE, FALSE, NULL)),
		broadcasted_(false)
	{
		assert(mu_);
	}

	Condition::~Condition()
	{
		::CloseHandle(sema_);
		::CloseHandle(event_);
	}

	void Condition::wait()
	{
		wait_mtx_.lock();
		++waiting_;
		assert(waiting_ > 0);
		wait_mtx_.unlock();
		::SignalObjectAndWait(mu_->mutex_, sema_, INFINITE, FALSE);
		wait_mtx_.lock();
		bool last = broadcasted_ && (--waiting_ == 0);
		assert(waiting_ >= 0);
		wait_mtx_.unlock();
		if (last)
		{
			::SignalObjectAndWait(event_, mu_->mutex_, INFINITE, FALSE);
		}
		else
		{
			::WaitForSingleObject(mu_->mutex_, INFINITE);
		}
	}

	void Condition::signal()
	{
		wait_mtx_.lock();
		bool waiters = waiting_ > 0;
		wait_mtx_.unlock();
		if (waiters)
		{
			::ReleaseSemaphore(sema_, 1, 0);
		}
	}

	void Condition::signalAll()
	{
		wait_mtx_.lock();
		broadcasted_ = (waiting_ > 0);
		if (broadcasted_)
		{
			::ReleaseSemaphore(sema_, waiting_, 0);
			wait_mtx_.unlock();
			::WaitForSingleObject(event_, INFINITE);
			broadcasted_ = false;
		}
		else
		{
			wait_mtx_.unlock();
		}
	}
}