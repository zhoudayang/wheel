//
// Created by zhouyang on 2016/10/11.
//

#ifndef HASH_TABLE_HASH_OBJECT_H
#define HASH_TABLE_HASH_OBJECT_H

#include <string>

class HashObject {
public:
    ~HashObject() {}

    std::string &GetKey() {
        return key_;
    }

    std::string &GetValue() {
        return value_;
    }

    void setKey(const std::string key) {
        key_ = key;
    }

    void setValue(const std::string value) {
        value_ = value;
    }

    void SetAsDummyKey() {
        key_ = GetDummyKey();
        value_ = "";
    }

    void setObject(HashObject *object) {
        key_ = object->GetKey();
        value_ = object->GetValue();
    }

    static const std::string GetDummyKey() {
        return "<Dummy>";
    }

    static const std::string GetNullKey() {
        return "<Null>";
    }

private:
    std::string key_;
    std::string value_;
};


#endif //HASH_TABLE_HASH_OBJECT_H
