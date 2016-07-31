#ifndef ATOMIC_H
#define ATOMIC_H

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace detail {
    // 原子操作类
    template<typename T>
    class AtomicIntergerT : boost::noncopyable {
    public:
        AtomicIntergerT() : value_(0) { }

        //如果原来的值为０,将其设置为０,并返回之前的值
        //实际上就是返回之前设置的值
        T get() {
            return __sync_val_compare_and_swap(&value_, 0, 0);
        }

        T getAndAdd(T x) {
            return __sync_fetch_and_add(&value_, x);
        }

        //返回的结果还要加上x
        T addAndGet(T x) {
            return getAndAdd(x) + x;
        }

        T incrementAndGet() {
            return addAndGet(1);
        }

        T decrementAndGet() {
            return addAndGet(-1);
        }

        void add(T x) {
            getAndAdd(x);
        }

        void increment() {

            incrementAndGet();
        }

        void decrement() {
            decrementAndGet();
        }

        //先返回再设置
        T getAndSet(T newValue) {
            return __sync_lock_test_and_set(&value_, newValue);
        }

    private:
        //volatile关键字可以用来提醒编译器它后面所定义的变量随时有可能改变，因此编译后的程序每次需要存储或读取这个变量的时候，都会直接从变量地址中读取数据。
        // 如果没有volatile关键字，则编译器可能优化读取和存储，可能暂时使用寄存器中的值，如果这个变量由别的程序更新了的话，将出现不一致的现象。volatile关键字可以用来提醒编译器它后面所定义的变量随时有可能改变，因此编译后的程序每次需要存储或读取这个变量的时候，都会直接从变量地址中读取数据。如果没有volatile关键字，则编译器可能优化读取和存储，可能暂时使用寄存器中的值，如果这个变量由别的程序更新了的话，将出现不一致的现象。
        volatile T value_;


    };

    typedef detail::AtomicIntergerT<int32_t> AtomicInt32;
    typedef detail::AtomicIntergerT<int64_t> AtomicInt64;
}

#endif