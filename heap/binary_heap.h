#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>

using namespace std;

template<typename Comparable>
class BinaryHeap {
public:
    explicit BinaryHeap(int capacity = 100) : array(capacity + 1), currentSize(0) {
    }

    explicit BinaryHeap(const vector<Comparable> &items) :
            array(items.size() + 1), currentSize(items.size()) {
        //将数组复制到指定位置
        for (int i = 0; i < items.size(); ++i)
        {
            array[i + 1] = items[i];
        }
        //然后进行建堆处理
        buildHeap();
    }

    //返回最小值
    const Comparable &findMin() const {
        if (isEmpty())
            throw;
        return array[1];
    }


    void insert(const Comparable &x) {
        if (currentSize == array.size() - 1)
            array.resize(array.size() * 2);

        // siftup
        int hole = ++currentSize;
        Comparable copy = x;

        array[0] = std::move(copy);
        for (; x < array[hole / 2]; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = std::move(array[0]);
    }

    void insert(Comparable &&x) {
        if (currentSize == array.size() - 1)
            array.resize(array.size() * 2);

        // sift up
        int hole = ++currentSize;
        for (; hole > 1 && x < array[hole / 2]; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = std::move(x);
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    //删除最小的那个元素，并且将最后一个元素调整到堆的头部，并且进行siftDown处理
    void deleteMin() {
        if (isEmpty())
            throw;
        array[1] = std::move(array[currentSize--]);
        siftDown(1);
    }


    void deleteMin(Comparable &min) {
        if (isEmpty())
            throw;
        //store min element
        min = std::move(array[1]);
        //move end element to front of the heap
        array[1] = std::move(array[currentSize--]);
        //siftdown the heap
        siftDown(1);
    }

    void makeEmpty() {
        currentSize = 0;
    }

private:
    int currentSize;
    vector<Comparable> array;

    void buildHeap() {
        for (int i = currentSize / 2; i > 0; --i)
            siftDown(i);
    }

    void siftDown(int hole) {
        int child;
        Comparable tmp = std::move( array[ hole ] );

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ] < array[ child ] )
                ++child;
            if( array[ child ] < tmp )
                array[ hole ] = std::move( array[ child ] );
            else
                break;
        }
        array[ hole ] = std::move( tmp );
    }
};

#endif