#include "cuckoo_hash.h"

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
int nextPrime(int num)
{
    if (num%2==0)
        ++num;
    while (!is_prime(num))
        num += 2;
    return num;
}

int hashCode(const std::string& key)
{
    int hashVal = 0;
    for (auto ch:key)
        hashVal = 37*hashVal+ch;
    return hashVal;
}

int hashCode(int key)
{
    return key;
}

