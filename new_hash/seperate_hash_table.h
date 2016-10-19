//
// Created by zhouyang on 2016/10/18.
//

#ifndef HASH_SEPERATE_HASH_TABLE_H
#define HASH_SEPERATE_HASH_TABLE_H

#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <algorithm>

//calculate hash value
template<typename Key>
class hash {
public:
    size_t operator()(const Key& k) const;
};

using std::find;
using std::end;
using std::begin;

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

//find if a given number is a prime
bool is_prime(size_t num)
{
    if (num<2)
        return false;
    for (int i = 2; i*i<=num; ++i)
    {
        if (num%i==0)
            return false;
    }
    return true;
}

//get next prime after num
size_t nextPrime(size_t num)
{
    while (!is_prime(num))
        ++num;
    return num;
}



//需要针对HashObj对hash类进行偏特化处理

template<typename HashObj>
class HashTable {
public:

    explicit HashTable(int size = 101)
            :theLists(size),
             currentSize(0)
    {

    }

    bool contains(const HashObj& x) const
    {
        auto& whichList = theLists[myhash(x)];
        return std::find(std::begin(whichList), std::end(whichList), x)!=std::end(whichList);
    }

    bool insert(const HashObj& x)
    {
        auto& whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x)!=end(whichList))
        {
            return false;
        }
        whichList.push_back(x);
        //进行再散列
        if (++currentSize>theLists.size())
            rehash();
        return true;
    }

    bool insert(HashObj&& x)
    {
        auto& whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x)!=end(whichList))
        {
            return false;
        }
        whichList.push_back(std::move(x));
        assert(whichList.size());
        if (++currentSize==theLists.size())
            rehash();
        return true;
    }

    bool remove(const HashObj& x)
    {
        auto& whichList = theLists[myhash(x)];
        auto it = find(begin(whichList), end(whichList), x);
        if (it==end(whichList))
            return false;
        whichList.erase(it);
        --currentSize;
        return true;
    }

    void makeEmpty()
    {
        for (auto& theList:theLists)
        {
            theList.clear();
        }
    }

private:
    std::vector<std::list<HashObj>> theLists;
    int currentSize;

    void rehash()
    {
        std::vector<std::list<HashObj>> oldLists = theLists;
        //resize to new capacity
        theLists.resize(nextPrime(2*theLists.size()));
        //init theLists
        for (auto& thisList:theLists)
            thisList.clear();
        currentSize = 0;
        //insert old element
        for (auto& thisList :oldLists)
        {
            for (auto& x:thisList)
                insert(std::move(x));
        }
    }

    //calculate hashTable index according to hash value calculated by hash<HashObj>
    size_t myhash(const HashObj& x) const
    {
        static hash<HashObj> hf;
        return hf(x)%theLists.size();
    }

};

#endif //HASH_SEPERATE_HASH_TABLE_H
