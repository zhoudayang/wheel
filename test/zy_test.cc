#include "zy_test.h"

#include <vector>
#include <string>
#include <stdlib.h>
#include <memory>

namespace zy
{
namespace test
{
namespace
{
struct Test
{
  const char* base;
  const char* name;
  void (*func)();
};
std::unique_ptr<std::vector<Test> > tests;
}

bool RegisterTest(const char* base, const char* name, void (*func)())
{
  if(!tests)
  {
    tests.reset(new std::vector<Test>);
  }
  Test t;
  t.base = base;
  t.name = name;
  t.func = func;
  tests->push_back(t);
  return true;
}

int RunAllTests()
{
  int num = 0;
  if(tests)
  {
    for(const auto& test : *tests)
    {
      fprintf(stderr, "==== Test %s.%s\n", test.base, test.name);
      (*test.func)();
      ++ num;
    }
  }
  fprintf(stderr, "==== PASSED %d tests\n", num);
  return 0;
}

} // namespace test
} // namespace zy
