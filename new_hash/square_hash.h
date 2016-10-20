#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <cmath>
#include <string>

using std::vector;

//find if a given number is a prime
bool is_prime(size_t num)
{
    if (num==2 || num==3)
        return true;
    if (num==1 || num%2==0)
        return false;
    for (int i = 3; i*i<=num; i += 2)
    {
        if (num%i==0)
            return false;
    }
    return true;
}

//get next prime after num
size_t nextPrime(size_t num)
{
    if(num%2==0)
        ++num;
    while (!is_prime(num))
        num+=2;
    return num;
}

//calculate hash value
template<typename Key>
class hash {
public:
    size_t operator()(const Key& k) const;
};

template<>
class hash<std::string> {
public:
    size_t operator()(const std::string& key)
    {
        size_t hashVal = 0;
        for (char ch:key)
        {
            hashVal = 37*hashVal+ch;
        }
        return hashVal;
    }
};

//you need to define your own hash function of give HashObj

template<typename HashObj>
class HashTable {
public:
    explicit HashTable(int size = 101)
            :array(nextPrime(size))
    {
        makeEmpty();
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (auto& entry:array)
        {
            entry.info = EMPTY;
        }
    }

    bool contains(const HashObj& x) const
    {
        return isActive(findPos(x));
    }

    bool insert(const HashObj& x)
    {
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;
        if (++currentSize>array.size()/2)
            rehash();
        return true;
    }

    bool insert(HashObj&& x)
    {
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;
        array[currentPos].element = std::move(x);
        array[currentPos].info = ACTIVE;
        if (++currentSize>array.size()/2)
            rehash();
        return true;
    }

    bool remove(const HashObj& x)
    {
        int currentPos = findPos(x);
        if (!isActive(currentPos))
            return false;
        array[currentPos].info = DELETED;
        return true;
    }

    enum EntryType {
        ACTIVE, EMPTY, DELETED
    };
private:

    struct HashEntry {
        HashObj element;
        EntryType info;

        HashEntry(const HashObj& e = HashObj{}, EntryType i = EMPTY)
                :element(e),
                 info(i)
        {

        }

        HashEntry(HashObj&& e, EntryType i = EMPTY)
                :element(std::move(e)),
                 info(i)
        {

        }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info==ACTIVE;
    }

    int findPos(const HashObj& x) const
    {
        int offset = 1;
        int currentPos = myhash(x);
        while (array[currentPos].info!=EMPTY && array[currentPos].element!=x)
        {
            currentPos += offset;
            offset += 2;
            if (currentPos>=array.size())
            {
                currentPos -= array.size();
            }
        }
        return currentPos;
    }

    void rehash()
    {
        vector<HashEntry> oldArray = array;
        //resize new capacity
        array.resize(nextPrime(2*oldArray.size()));
        //init array
        for (auto& entry:array)
            entry.info = EMPTY;
        //reset currentSize
        currentSize = 0;
        //insert entry
        for (auto& entry:oldArray)
            if (entry.info==ACTIVE)
                insert(std::move(entry.element));
    }

    size_t myhash(const HashObj& x) const
    {
        static hash<HashObj> hf;
        return hf(x)%array.size();
    }

};

#endif