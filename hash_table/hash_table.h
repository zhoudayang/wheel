//
// Created by zhouyang on 2016/10/11.
//

#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "hash_object.h"


class HashTable {
public:
    explicit HashTable(const int size);

    ~HashTable();

    HashTable(const HashTable &) = delete;

    HashTable &operator=(const HashTable &) = delete;

    void Add(HashObject *object);

    bool Exists(const std::string &key);

    const std::string Get(const std::string &key);

    void Remove(const std::string &key);

    void PrintDebug();

private:
    int Hash(const std::string &key);


    int size_;
    HashObject *data_;
};



#endif //HASH_TABLE_HASH_TABLE_H
