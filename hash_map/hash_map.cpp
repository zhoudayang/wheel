#include <iostream>
#include <boost/functional/hash.hpp>
#include <unordered_map>

using namespace std;

struct MatElem
{
  uint32_t uin;
  uint32_t msg_id;
  uint32_t idx;
};

class EqualFunc
{
 public:
  bool operator()(const MatElem &a, const MatElem &b) const
  {
    return (a.uin == b.uin) && (a.msg_id == b.msg_id) && (a.idx == b.idx);
  }
};

class Hasher
{
 public:
  size_t operator()(const MatElem &key) const
  {
    using boost::hash_value;
    using boost::hash_combine;

    std::size_t seed = 5381;

    hash_combine(seed, hash_value(key.uin));
    hash_combine(seed, hash_value(key.msg_id));
    hash_combine(seed, hash_value(key.idx));

    return seed;
  }
};

std::string to_string(const MatElem &a)
{
  return to_string(a.uin) + ", " + to_string(a.msg_id) + ", " + to_string(a.idx) + "\n";
}

int main()
{
  unordered_map<MatElem, int, Hasher, EqualFunc> container;
  MatElem a{1, 2, 3};
  MatElem b{2, 3, 4};

  for (int i = 0; i < 3; ++i)
  {
    container[a] += 1;
  }
  for (int j = 0; j < 2; ++j)
  {
    container[b] += 2;
  }

  for (auto it = container.cbegin(); it != container.cend(); ++it)
  {
    cout << to_string((it->first));
    cout << it->second << endl;
  }

  return 0;
}
