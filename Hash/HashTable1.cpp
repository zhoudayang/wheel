#include<iostream>

using namespace std;

class HashItem {
private:
    int key, val;
public:
    HashItem(int key, int val) : key(key), val(val) { }

    const int &getKey() {
        return key;
    }

    const int &getVal() {
        return val;
    }
};

class HashTable {
private:
    static const int SIZE = 256;
    //指向 HashItem * 类型的数组
    HashItem **table;
public:
    HashTable() {
        table = new HashItem *[SIZE];
        for (int i = 0; i < SIZE; i++) {
            //将指针数组中的每一项初始化为NULL
            table[i] = nullptr;
        }
    }

    //此处没有处理碰撞检测
    void set(int key, int val) {
        int idx = key % SIZE;
        if (table[idx]) {
            delete table[idx];
            //注意空悬指针
            table[idx] = nullptr;
        }
        table[idx] = new HashItem(key, val);
    }

    //此处没有处理碰撞检测
    const int get(int key) {
        int idx = key % SIZE;
        return table[idx] ? table[idx]->getVal() : -1;
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++)
            if (table[i])
                delete table[i];
        delete[]table;
    }
};

class HashTable1 {
private:
    static const int SIZE = 256;
    HashItem **table;
public:
    HashTable1() {
        table = new HashItem *[SIZE];
        for (int i = 0; i < SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void set(int key, int val) {
        int idx = key % SIZE;
        int count = 0;
        while (table[idx] && table[idx]->getKey() != key) {
            idx = (idx + 1) % SIZE;
            count++;
            if (count == SIZE) {
                //这里没有进行扩容处理
                cout << "capacity is not enough!" << endl;
                return;
            }
        }
        if (table[idx]) {
            delete table[idx];
            table[idx] = nullptr;
        }
        table[idx] = new HashItem(key, val);
    }

    const int get(int key) {
        int idx = key % SIZE;
        int count = 0;
        while (table[idx] && table[idx]->getKey() != key) {
            idx = (idx + 1) % SIZE;
            count++;
            //can not find key
            if (count == SIZE) {
                return -1;
            }
        }
        return table[idx] ? table[idx]->getVal() : -1;
    }

    ~HashTable1() {
        for (int i = 0; i < SIZE; i++)
            if (table[i])
                delete table[i];
        delete[] table;
    }

};
//todo 没有实现hash表的自动扩容
int main() {
    HashTable1 table;
    for (int i = 0; i < 256; i++)
        table.set(i, i + 1);
    for (int i = 0; i < 256; i++)
        cout << table.get(i) << endl;

    return 0;
}
