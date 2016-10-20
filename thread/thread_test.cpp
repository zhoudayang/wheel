#include "thread.h"

#include <cstdio>
#include <string>
#include <boost/bind.hpp>

void mysleep(int seconds)
{
	zy::Util::sleepMs(seconds * 1000);
}

void threadFunc1()
{
	printf("tid = %ld \n", zy::Util::tid());
}

void threadFunc2(int x)
{
	printf("tid = %ld , x = %d \n", zy::Util::tid(),x);
}

void threadFunc3()
{
	printf("tid = %ld \n", zy::Util::tid());
	zy::Util::sleepMs(100);
}

class Foo
{
public:
	explicit Foo(double x)
		:x_(x)
	{
		
	}

	void memberFunc1()
	{
		printf("tid = %ld , x = %f \n", zy::Util::tid(), x_);
	}

	void memberFunc2(const std::string & text)
	{
		printf("tid = %d, Foo::x_ = %f, text = %s\n", zy::Util::tid(), x_, text.c_str());
	}
	
private:
	double x_;
};



using namespace zy;
int main()
{
	printf("pid = %ld ,tid = %ld\n", Util::getpid(), Util::tid());
	
	zy::Thread t1(threadFunc1);
	t1.start();
	t1.join();

	zy::Thread t2(boost::bind(threadFunc2,66),"thread for free function with argument");
	t2.start();
	t2.join();

	Foo foo(12.34);
	zy::Thread t3(boost::bind(&Foo::memberFunc1, &foo), "thread for member function without argument");
	t3.start();
	t3.join();

	zy::Thread t4(boost::bind(&Foo::memberFunc2, boost::ref(foo), std::string("zhou yang")));
	t4.start();
	t4.join();

	{
		zy::Thread t5(threadFunc3);
		t5.start();
		//t5 may sestruct earlier than thread creation
	}
	mysleep(2);
	{
		zy::Thread t6(threadFunc3);
		t6.start();
		mysleep(2);
		//t6 may sestruct earlier than thread creation
	}
	boost::detail::Sleep(2000);
	printf("number of created threads %d \n", zy::Thread::numCreated());

	return 0;
}