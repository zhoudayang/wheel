#include <iostream>
#include <string>
#include <cassert>
#include <random>

#include "square_hash.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

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