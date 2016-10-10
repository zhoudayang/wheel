//
// Created by zhouyang on 2016/10/11.
//

#include "hash_table.h"

HashTable::HashTable(const int size) :
        size_(size),
        data_(new HashObject[size]) {
    assert(data_ != nullptr);
    //init with nullptr
    for (int i = 0; i < size_; ++i)
    {
        data_[i].setKey(HashObject::GetNullKey());
    }
}

HashTable::~HashTable() {
    delete[] data_;
}

int HashTable::Hash(const std::string &key) {
    int hash = 0;
    for (auto ch:key)
    {
        hash = hash * 31 + ch;
    }
    return abs(hash % key.size());
}

bool HashTable::Exists(const std::string &key) {
    int index = Hash(key);
    int origin_index{index};
    bool found = false;
    while (data_[index].GetKey() != HashObject::GetNullKey())
    {
        if (data_[index].GetKey() == key)
        {
            found = true;
            break;
        }
        index = (index + 1) % size_;
        //如果回到了原始的index，break
        if (index == origin_index)
        {
            break;
        }
    }
    return found;
}

void HashTable::Add(HashObject *object) {
    int index = Hash(object->GetKey());
    int origin_index = index;
    int dummyIndex = -1;
    bool found = false;
    while (data_[index].GetKey() != HashObject::GetNullKey())
    {
        if (data_[index].GetKey() == object->GetKey())
        {
            found = true;
            break;
        }
        else if (data_[index].GetKey() == HashObject::GetDummyKey())
        {
            dummyIndex = index;
        }
        index = (index + 1) % size_;
        //没有空余的空间
        if (index == origin_index)
        {
            return;
        }
    }
    //优先使用dummy position
    if (!found && dummyIndex != -1)
    {
        index = dummyIndex;
    }
    data_[index].setObject(object);
}

void HashTable::Remove(const std::string &key) {
    int index = Hash(key);
    int origin_index = index;
    while (data_[index].GetKey() != HashObject::GetNullKey())
    {
        if (data_[index].GetKey() == key)
        {
            data_[index].SetAsDummyKey();
            break;
        }
        index = (index + 1) % size_;
        if (index == origin_index)
            break;
    }
}

const std::string HashTable::Get(const std::string &key) {
    int index = Hash(key);
    int origin_index{index};
    while (data_[index].GetKey() != HashObject::GetNullKey())
    {
        if (data_[index].GetKey() == key)
        {
            return data_[index].GetValue();
        }
        index = (index + 1) % size_;
        if (index == origin_index)
        {
            break;
        }
    }
    return nullptr;
}

void HashTable::PrintDebug() {
    for (int i = 0; i < size_; ++i)
    {
        std::cout << i << ": " << data_[i].GetKey() << ":" << data_[i].GetValue() << std::endl;
    }
}