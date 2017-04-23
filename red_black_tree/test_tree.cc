#include "red_black_tree.h"

#include <unordered_set>
#include <assert.h>

using namespace zy;
using namespace std;

// normal exit without output means okay.
int main()
{
  RedBlackTree<int, int> tree;
  srand(time(0));
  unordered_set<int> arr;

  while(arr.size() < 1000000)
  {
    auto value = rand();
    arr.insert(value);
    tree.put(value, value);
  }
  assert(arr.size() == tree.size());

  for(auto& val : arr)
  {
    assert(tree.get(val));
  }

  for(auto& val : arr)
  {
    tree.deleteNode(val);
  }
  assert(tree.size() == 0);

  for(auto& val : arr)
  {
    tree.put(val, val);
  }

  for(int i = 0; i < arr.size(); ++ i)
  {
    tree.deleteMax();
  }
  assert(tree.size() == 0);

  for(auto& val : arr)
  {
    tree.put(val, val);
  }
  for(int i = 0; i < arr.size(); ++ i)
  {
    tree.deleteMin();
  }
  assert(tree.size() == 0);

  return 0;
}
