#include <iostream>
#include <cassert>
#include "kmp.h"

using namespace std;
using namespace zy;
int main() {

  assert(kmp("hello world", "world") == 6);
  assert(kmp("test it", "test it") == 0);
  assert(kmp("abeabefgabeabcea","abc") == 11);
  assert(kmp("abcsla","abds")==-1);


  return 0;
}