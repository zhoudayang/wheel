//
// Created by zhouyang on 2016/10/15.
//

#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

//key idea
//使用 unsigned int 存放中间结果，并且注意溢出问题
int atoi(const char *digits)
{
  unsigned int n = 0;
  if (!digits)
  {
    return 0;
  }
  while (isspace(*digits))
  {
    ++digits;
  }
  int sign = 1;
  if (*digits == '+' || *digits == '-')
  {
    if (*digits == '-')
    {
      sign = -1;
    }
    ++digits;
  }
  while (isdigit(*digits))
  {
    int c = *digits - '0';
    if (sign > 0 && (n > INT_MAX / 10 || (n == INT_MAX / 10 && c > INT_MAX % 10)))
    {
      n = INT_MAX;
      break;
    }
    else if (sign < 0 && (n > static_cast<unsigned>(INT_MAX) / 10
        || (n == static_cast<unsigned>(INT_MIN) / 10 && c > static_cast<unsigned>(INT_MIN) % 10)))
    {
      n = INT_MIN;
      break;
    }
    n = n * 10 + c;
    ++digits;
  }
  return sign > 0 ? n : -n;
}

int main()
{
  auto max_str = to_string(INT_MAX);
  auto min_str = to_string(INT_MIN);
  cout << max_str << " : " << atoi(max_str.c_str()) << endl;
  cout << min_str << " : " << atoi(min_str.c_str()) << endl;

  for (int i = 0; i < 1000; ++i)
  {
    int value = rand();
    int negative_value = -value;
    auto value_str = to_string(value);
    auto negative_str = to_string(negative_value);
    cout << value << " : " << atoi(value_str.c_str()) << endl;
    cout << negative_value << " : " << atoi(negative_str.c_str()) << endl;
  }

  cout << "787878787878787878 : " << atoi("787878787878787878") << endl;
  cout << "-787878787878787878 : " << atoi("-787878787878787878") << endl;

  return 0;
}
