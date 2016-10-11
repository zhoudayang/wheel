#include "Vector.h"

#include <iostream>


using std::cout;
using std::endl;


class test {
public:
    test() :
            val_(0) {
        cout << "costructor" << endl;
    }

    test(const test &elem) :
            val_(elem.val_) {
        cout << "copy constructor" << endl;
    }

    test(test &&elem) :
            val_(std::move(elem.val_)) {
        cout << "move copy constructor" << endl;
    }

    test &operator=(const test &elem) {
        val_ = elem.val_;
        cout << "copy assignment function" << endl;
        return *this;
    }

    test &operator=(test &&elem) {
        if (this != &elem)
        {
            val_ = std::move(elem.val_);
        }
        cout << "move copy assignment function" << endl;
        return *this;
    }

    void print() const {
        cout << "val: " << val_ << endl;
    }

    ~test(){
        cout<<"destructor"<<endl;
    }

private:
    int val_;
};


int main() {
    Vector<test> container;
    for (int i = 0; i < 1; ++i)
    {
        container.push_back(test());
    }
    for(auto it = container.begin();it!=container.end();++it){
        it->print();
    }



    return 0;
}