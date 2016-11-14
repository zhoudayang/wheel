#include "random.h"

#include <iostream>
#include <unordered_map>
#include <stdint.h>
#include <cassert>

using namespace zy;
using namespace std;

int main() {

  unordered_map<uint32_t, int> container;

  Random random(1200);
  int max_count = 0;
  for (int i = 0; i < 1000000; i++) {
    max_count = max(++container[random.Next()], max_count);
  }
  cout << "after generate 1000000 random numbers, the same value maximum occur time is " << max_count << endl;

  for (int i = 0; i < 470; i++)
    if (random.OneIn(47))
      cout << "get on in 47" << endl;

  for (int i = 0; i < 10000; i++) {
    uint32_t random_number = random.Uniform(10000);
    assert(random_number < 10000 and random_number >= 0);
  }

}
