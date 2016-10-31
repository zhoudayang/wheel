//
// Created by zhouyang on 2016/10/31.
//

#include "SkipNode.h"



using namespace zy;

template<typename T>
SkipNode<T>::SkipNode(int height) :height_(height), data_(nullptr) {
  nodes = new SkipNode<T> *[height + 1];
  for (int i = 0; i <= height_; ++i)
    nodes[i] = nullptr;
}

template<typename T>
SkipNode<T>::SkipNode(const T &data, int height) :height_(height), data_(new T(data)) {
  nodes = new SkipNode<T> *[height + 1];
  for (int i = 0; i <= height_; ++i) {
    nodes[i] = nullptr;
  }
}

template<typename T>
SkipNode<T>::~SkipNode() {
  delete data_;
  delete[] nodes;
}

template<typename T>
int SkipNode<T>::getNodeHeight() const {
  return height_;
}

template<typename T>
T *SkipNode<T>::getData() const {
  return data_;
}

namespace zy {
template
class SkipNode<int>;
}