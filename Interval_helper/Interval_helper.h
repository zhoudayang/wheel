#pragma once

#include <boost/timer.hpp>
#include <boost/noncopyable.hpp>
#include <thread>


//helper class to control run time 
class Interval_helper :boost::noncopyable {
public:
	Interval_helper(double interval) :
		interval_(interval),
		now_()
	{

	}

	//注：windows的时间精度是毫秒级别，故而选择的sleep精度也是毫秒
	//如果是 linux,时间精度可以更改为微秒
	~Interval_helper() {
		int diff = static_cast<int>(1000.0*(interval_ - now_.elapsed()));
		//剩余时间间隔大于0才sleep
		if (diff > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(diff));
		}
	}

	//返回最小时间精度
	double elapsed_min() const {
		return now_.elapsed_min();
	}

	double elapsed() {
		return now_.elapsed();
	}
private:
	double interval_;
	boost::timer now_;
};
