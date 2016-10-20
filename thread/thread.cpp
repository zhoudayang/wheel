#include <boost/weak_ptr.hpp>
#include "thread.h"
#include <process.h>


namespace zy {


	void Util::sleepMs(DWORD millisecond)
	{
		Sleep(millisecond);
	}

	DWORD Util::tid()
	{
		return GetCurrentThreadId();
	}

	DWORD Util::getpid()
	{
		return GetCurrentProcessId();
	}

	namespace detail
	{
		struct ThreadData
		{
			typedef zy::Thread::ThreadFunc ThreadFunc;
			ThreadFunc func_;
			std::string &name_;
			boost::weak_ptr<DWORD> wkTid_;

			ThreadData(const ThreadFunc & func, std::string & name, const boost::shared_ptr<DWORD> & tid)
				:func_(func),
				name_(name),
				wkTid_(tid) {}

			void runInThread()
			{
				DWORD tid = GetCurrentThreadId();
				boost::shared_ptr<DWORD> ptid = wkTid_.lock();
				if (ptid)
				{
					//set thread Id
					*ptid = tid;
					ptid.reset();
				}
				if (name_.empty())
					name_ = "zyThread";
				try
				{
					func_();
					name_ += "finished";
				}
				catch (const std::exception & ex)
				{

					fprintf(stderr, "exception caught in Thread %s\n", name_.c_str());
					fprintf(stderr, "reason: %s\n", ex.what());
					name_ += "crashed";
					abort();
				}
				catch (...)
				{
					fprintf(stderr, "unknown exception caught in Thread %s \n", name_.c_str());
					name_ += "crashed";
					throw;
				}
			}
		};

		unsigned int __stdcall startThread(PVOID obj)
		{
			ThreadData * data = static_cast<ThreadData *>(obj);
			data->runInThread();
			delete data;
			return 0;
		}
	}
}
using namespace zy;

std::atomic<int>  Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const std::string& name)
	:started_(false),
	joined_(false),
	threadId_(NULL),
	tid_(new DWORD(0)),
	func_(func),
	name_(name)
{
	//set default thread name if thread name is empty 
	setDefaultName();
}

Thread::Thread(ThreadFunc&& func, const std::string& name)
	:started_(false),
	joined_(false),
	threadId_(NULL),
	tid_(new DWORD(0)),
	func_(func),
	name_(name)
{
	//set default thread name if thread name is empty 
	setDefaultName();
}

void Thread::setDefaultName()
{
	int num = ++numCreated_;
	if (name_.empty())
	{
		char buf[32];
		snprintf(buf, sizeof buf, "Thread%d", num);
		name_ = buf;
	}
}

Thread::~Thread()
{
	if (started_ && !joined_)
	{
		CloseHandle(threadId_);
	}
}

void Thread::start()
{
	assert(!started_);
	started_ = true;
	detail::ThreadData * data = new detail::ThreadData(func_, name_, tid_);

	if ((threadId_ = (HANDLE)_beginthreadex(NULL, 0, detail::startThread, data, 0, NULL)) == nullptr)
	{
		started_ = false;
		delete data;
		abort();
	}
}

void Thread::join()
{
	assert(started_);
	assert(!joined_);
	joined_ = true;
	WaitForSingleObject(threadId_, INFINITE);
}

