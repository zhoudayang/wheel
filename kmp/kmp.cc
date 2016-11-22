#include <string>
#include <vector>

using std::string;
using std::vector;

namespace zy {

// 求给定字符串str的最长相等前缀后缀
vector<int> common_length(const string &str) {
  vector<int> length(str.size(), 0);
  int k = 0;
  for (size_t i = 1; i < str.size(); ++i) {
    while (str[i] != str[k] and k > 0) {
      k = length[k - 1];
    }
    if (str[i] == str[k]) {
      length[i] = ++k;
    } else
      length[i] = 0;
  }
  return length;
}

// find if p exist in s
int kmp(const string &s, const string &p) {
  if (s.size() < p.size())
    return -1;
  vector<int> next = common_length(p);
  next.insert(next.begin(), -1);
  int s_len = s.length();
  int p_len = p.length();
  int i = 0, j = 0;
  while (i < s_len and j < p_len) {
    if (j == -1 or s[i] == p[j]) {
      ++i;
      ++j;
    } else {
      j = next[j];
    }
  }
  if (j == p_len)
    return i - j;
  return -1;
}

}