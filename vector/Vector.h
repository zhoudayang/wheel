//
// Created by zhouyang on 2016/10/12.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>


template<typename Object>
class Vector {
public:
    explicit Vector(int initSize = 0) :
            theSize_(initSize),
            theCapacity_(initSize + SPACE_CAPACITY) {
        objects_ = new Object[theCapacity_];
    }

    Vector(const Vector &rhs) :
            theSize_(rhs.theSize_),
            theCapacity_(rhs.theCapacity_),
            objects_(nullptr) {
        objects_ = new Object[theCapacity_];
        for (int k = 0; k < theSize_; ++k)
        {
            objects_[k] = rhs.objects_[k];
        }
    }

    Vector &operator=(const Vector &rhs) {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~Vector() {
        delete[] objects_;
    }

    Vector(Vector &&rhs) :
            theSize_(rhs.theSize_),
            theCapacity_(rhs.theCapacity_),
            objects_(rhs.objects_) {
        rhs.objects_ = nullptr;
        rhs.theSize_ = 0;
        rhs.theCapacity_ = 0;
    }

    Vector &operator=(Vector &&rhs) {
        std::swap(theSize_, rhs.theSize_);
        std::swap(theCapacity_, rhs.theCapacity_);
        std::swap(objects_, rhs.objects_);

        return *this;
    }

    void reserve(int newCapacity) {
        if (newCapacity < theSize_)
        {
            return;
        }
        Object *newArray = new Object[newCapacity];
        for (int k = 0; k < theSize_; k++)
        {
            newArray[k] = std::move(objects_[k]);
        }
        theCapacity_ = newCapacity;
        std::swap(objects_, newArray);
        delete[] newArray;
    }


    void resize(int newSize) {
        if (newSize > theCapacity_)
            reserve(newSize * 2);
        theSize_ = newSize;
    }
    
    //clear the vector 
    void clear(){
        theSize_ = 0;
    }

    Object &operator[](int index) {
        return objects_[index];
    }

    const Object &operator[](int index) const {
        return objects_[index];
    }

    int size() const {
        return theSize_;
    }

    bool empty() const {
        return size() == 0;
    }

    int capacity() const {
        return theCapacity_;
    }

    void push_back(const Object &x) {
        if (theSize_ == theCapacity_)
        {
            reserve(theCapacity_ * 2 + 1);
        }
        objects_[theSize_++] = x;
    }

    void push_back(Object &&x) {
        if (theSize_ == theCapacity_)
        {
            reserve(theCapacity_ * 2 + 1);
        }
        objects_[theSize_++] = std::move(x);
    }

    void pop_back() {
        --theSize_;
    }

    const Object &back() const {
        return objects_[theSize_ - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() {
        return &objects_[0];
    }

    const_iterator begin() const {
        return &objects_[0];
    }

    iterator end() {
        return &objects_[theSize_];
    }

    const_iterator end() const {
        return &objects_[theSize_];
    }

    static const int SPACE_CAPACITY = 1;
private:
    int theSize_;
    int theCapacity_;
    Object *objects_;

};


#endif
