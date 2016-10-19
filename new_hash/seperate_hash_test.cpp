#include "seperate_hash_table.h"

#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> numbers;
    HashTable<std::string> table;
    for (int i = 0; i<1010; ++i)
    {
        numbers.push_back(rand());
        table.insert(std::to_string(numbers.back()));
    }

    for (int i = 0; i<1010; ++i)
    {
        assert(table.contains(std::to_string(numbers[i])));
    }

    for (int i = 0; i<1010; ++i)
    {
        table.remove(std::to_string(numbers[i]));
    }

    for (int i = 0; i<1010; ++i)
    {
        assert(!table.contains(std::to_string(numbers[i])));
    }

    return 0;
}