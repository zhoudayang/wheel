## AtomicPointer

> 原子指针类，支持并发读情况下的单线程修改

实现原理：禁止编译器优化造成的执行乱序，并且对指针的读或者写需要直接对应内存中的数据操作。


* only support x86_64
* refer to leveldb AtomicPointer 