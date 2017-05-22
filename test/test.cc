#include "zy_test.h"

namespace zy
{
namespace test
{
class example {};

TEST(example, test1)
{
  ASSERT_TRUE(true);
  ASSERT_EQ(1, 1);
  ASSERT_NE(2, 1);
  ASSERT_GE(3, 3);
  ASSERT_GT(4, 1);
  ASSERT_LE(1, 1);
  ASSERT_LT(1, 2);
}

TEST(example, test2)
{
  ASSERT_TRUE(false) << " because of spell";
}

}
}

int main()
{
  return zy::test::RunAllTests();
}
