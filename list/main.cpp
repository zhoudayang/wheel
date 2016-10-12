//
// Created by zhouyang on 16-10-12.
//
#include "list.h"
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

class test {
public:
    test()
            :
            val_(0)
    {
        //cout << "costructor" << endl;
    }

    explicit test(int val)
            :val_(val)
    {
        //cout << "constructor" << endl;
    }

    test(const test& elem)
            :
            val_(elem.val_)
    {
        //cout << "copy constructor" << endl;
    }

    test(test&& elem)
            :
            val_(std::move(elem.val_))
    {
        //cout << "move copy constructor" << endl;
    }

    test& operator=(const test& elem)
    {
        val_ = elem.val_;
        //cout << "copy assignment function" << endl;
        return *this;
    }

    test& operator=(test&& elem)
    {
        if (this!=&elem)
        {
            val_ = std::move(elem.val_);
        }
        //cout << "move copy assignment function" << endl;
        return *this;
    }

    void print() const
    {
        cout << "value= " << val_ << endl;
    }

    ~test()
    {
        //cout << "destructor" << endl;
    }

private:
    int val_;
};

int main()
{
    List<test> container;
//    上面涉及到这几次函数调用：首先创建零参数的test实例，然后利用复制构造函数赋值给Node中的成员data，复制完毕，将临时对象析构
//    因为初始化了head 和 tail,　所以上述调用进行了两次，最后将所有的node 中的data析构

    for (int i = 0; i<1; ++i)
    {
        container.push_back(test());
    }

    container.begin()->print();

    assert(container.size()==1);

    for(int i=0;i<10000;i++)
        container.push_back(test(i));
    assert(container.size() ==10001);


    container.clear();

    assert(container.size()==0);

    for(auto val:{1,2,3,4,5,6,7,8}){
        container.push_back(test(val));
    }

    assert(container.size()==8);

    auto it = container.begin();
    ++it;
    ++it;
    it = container.erase(it);
    cout<<endl;
    for(auto it=container.begin();it!=container.end();++it)
        it->print();
    cout<<endl;
    container.insert(it,test(1090));
    for(auto it=container.begin();it!=container.end();++it)
        it->print();



    return 0;
}