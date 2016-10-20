#pragma once

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <atomic>
#include <windows.h>


namespace zy
{
	namespace Util
	{
		void sleepMs(DWORD millisecond);

		DWORD tid();

		DWORD getpid();
	}

	class Thread :boost::noncopyable
	{
	public:
		typedef boost::function<void()> ThreadFunc;

		explicit Thread(const ThreadFunc & func, const std::string & name = std::string());

		explicit Thread(ThreadFunc && func, const std::string & name = std::string());

		~Thread();

		void start();

		void join();

		bool started() const
		{
			return started_;
		}

		DWORD tid() const
		{
			return *tid_;
		}

		const std::string name() const
		{
			return name_;
		}

		static int numCreated()
		{
			return numCreated_;
		}

	private:

		void setDefaultName();


		bool started_;
		bool joined_;
		//thread handle 
		HANDLE threadId_;
		//thread id 
		boost::shared_ptr<DWORD> tid_;
		ThreadFunc func_;
		std::string name_;
		static std::atomic<int> numCreated_;
	};

}
