//
// Created by fit on 16-10-19.
//

#ifndef HASH_CUCKOO_HASH_H
#define HASH_CUCKOO_HASH_H

#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "uniform_random.h"

template<typename AnyType>
class CuckooHashFamily {
public:
    size_t hash(const AnyType& x, int which) const;

    int getNumberOfFunctions();

    void generateNewFunctions();
};

template<int count>
class StringHashFamily {
public:
    StringHashFamily()
            :MULTIPLIERS(count)
    {
        generateNewFunctions();
    }

    /// return number of functions
    int getNumberOfFunctions() const
    {
        return count;
    }

    //generate new hash functions
    void generateNewFunctions()
    {
        for (auto& mult:MULTIPLIERS)
        {
            mult = r.nextInt();
        }
    }

    //calculate hash value according to index with value which of given key
    size_t hash(const std::string& x, int which) const
    {
        //get multiplier
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;
        //use multiplier to calculate hash value
        for (auto ch:x)
            hashVal = multiplier*hashVal+ch;
        return hashVal;
    }
private:
    std::vector<int> MULTIPLIERS;
    UniformRandom r;
};

int nextPrime(int n);

constexpr double MAX_LOAD = 0.4;

template<typename AnyType, typename HashFamily>
class HashTable {
public:
    explicit HashTable(int size = 101)
            :array(nextPrime(size))
    {
        numHashFunctions = hashFunctions.getNumberOfFunctions();
        rehashes = 0;
        makeEmpty();
    }

    bool contains(const AnyType& x) const
    {
        return findPos(x)!=-1;
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (auto& entry: array)
            entry.isActive = false;
    }

    bool insert(const AnyType& x)
    {
        if (contains(x))
            return false;
        //达到expand界限
        if (currentSize>=array.size()*MAX_LOAD)
            expand();
        return insertHelper1(x);
    }

    bool insert(AnyType&& x)
    {
        if (contains(x))
            return false;
        if (currentSize>=array.size()*MAX_LOAD)
            expand();
        return insertHelper1(std::move(x));
    }

    int size() const
    {
        return currentSize;
    }

    int capacity() const
    {
        return array.size();
    }

    bool remove(const AnyType& x)
    {
        int currentPos = findPos(x);
        //find none
        if (!isActive(currentPos))
            return false;
        //delete it
        array[currentPos].isActive = false;
        return true;
    }

private:
    struct HashEntry {
        AnyType element;
        bool isActive;

        HashEntry(const AnyType& e = AnyType(), bool a = false)
                :element{e}, isActive{a}
        {

        }
        HashEntry(AnyType&& e, bool a = false)
                :element{std::move(e)}, isActive{a}
        {

        }
    };

    vector<HashEntry> array;
    int currentSize;
    int numHashFunctions;
    int rehashes;
    UniformRandom r;
    HashFamily hashFunctions;

    static const int ALLOWED_REHASHES = 5;

    bool insertHelper1( const AnyType & xx )
    {
        const int COUNT_LIMIT = 100;
        AnyType x = xx;

        while( true )
        {
            int lastPos = -1;
            int pos;

            for( int count = 0; count < COUNT_LIMIT; ++count )
            {
                for( int i = 0; i < numHashFunctions; ++i )
                {
                    pos = myhash( x, i );

                    //get empty pos, insert it
                    if( !isActive( pos ) )
                    {
                        array[ pos ] = std::move( HashEntry{ std::move( x ), true } );
                        ++currentSize;
                        return true;
                    }
                }

                // None of the spots are available. Kick out random one
                //　替换任意一个
                int i = 0;
                do
                {
                    pos = myhash( x, r.nextInt( numHashFunctions ) );
                } while( pos == lastPos && i++ < 5 ); //避免替换到上一次的位置 pos!=lastPos

                lastPos = pos;
                //use pos to store the new element
                std::swap( x, array[ pos ].element );
                //now insert array[pos].element
            }

            //一次循环没有达成，直接expand
            if( ++rehashes > ALLOWED_REHASHES )
            {
                expand( );     // Make the table bigger
                rehashes = 0;
            }
                //每次循环不成，都会进行rehash
            else
                rehash( );
        }
    }

    bool insertHelper1( AnyType && x )
    {
        const int COUNT_LIMIT = 100;

        while( true )
        {
            int lastPos = -1;
            int pos;

            for( int count = 0; count < COUNT_LIMIT; ++count )
            {
                for( int i = 0; i < numHashFunctions; ++i )
                {
                    pos = myhash( x, i );

                    if( !isActive( pos ) )
                    {
                        array[ pos ] = std::move( HashEntry{ std::move( x ), true } );
                        ++currentSize;
                        return true;
                    }
                }

                // None of the spots are available. Kick out random one
                int i = 0;
                do
                {
                    pos = myhash( x, r.nextInt( numHashFunctions ) );
                } while( pos == lastPos && i++ < 5 );

                lastPos = pos;
                std::swap( x, array[ pos ].element );
            }

            if( ++rehashes > ALLOWED_REHASHES )
            {
                expand( );     // Make the table bigger
                rehashes = 0;
            }
            else
                rehash( );
        }
    }

    bool isActive(int currentPos) const
    {
        //valid pos and hash entry is valid
        return currentPos!=-1 && array[currentPos].isActive;
    }

    int findPos(const AnyType& x) const
    {
        for (int i = 0; i<numHashFunctions; ++i)
        {
            int pos = myhash(x, i);
            if (isActive(pos) && array[pos].element==x)
                return pos;
        }
        //try all function, buy find none, return -1
        return -1;
    }

    void expand()
    {
        //expand size of hash table and rehash it
        rehash(static_cast<int>(array.size()/MAX_LOAD));
    }

    void rehash()
    {
        //generate new hash function
        hashFunctions.generateNewFunctions();
        //rehash to new size
        rehash(array.size());
    }

    void rehash(int newSize)
    {
        vector<HashEntry> oldArray = array;
        ///resize array
        array.resize(nextPrime(newSize));
        for (auto& entry:array)
            entry.isActive = false;
        currentSize = 0;
        //insert active entry from hash table to new hash table
        for (auto& entry:oldArray)
            if (entry.isActive)
                insert(std::move(entry.element));
    }

    //调用which 对应的hash　function来计算hash值
    size_t myhash(const AnyType& x, int which) const
    {
        return hashFunctions.hash(x, which)%array.size();
    }

};

#endif //HASH_CUCKOO_HASH_H
