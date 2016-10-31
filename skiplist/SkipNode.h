//
// Created by zhouyang on 2016/10/31.
//

#ifndef SKIPLIST_SKIPNODE_H
#define SKIPLIST_SKIPNODE_H
namespace zy {

template<typename T>
class SkipNode {
 public:
  SkipNode **nodes;

  SkipNode(int height);

  SkipNode(const T &data, int height);

  ~SkipNode();

  T *getData() const;

  int getNodeHeight() const;

 private:
  //NO copying allowed
  SkipNode(const SkipNode<T> &);
  void operator=(const SkipNode<T> &);
  //max height of skiplist node
  int height_;
  // T *, a pointer to data
  T *data_;

};

}
#endif //SKIPLIST_SKIPNODE_H
