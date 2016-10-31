//
// Created by zhouyang on 2016/10/31.
//

#include "SkipList.h"
#include "RandomLevel.h"

using namespace zy;

template<typename T>
SkipList<T>::SkipList(int max_height, double probability)
    :max_height_(max_height),
     cur_height_(0),
     probability_(probability),
     random_(new RandomLevel(max_height_, probability_)),
     head_(new SkipNode<T>(max_height)) {

}

//traverse along the lowest linked list and delete each node
template<typename T>
SkipList<T>::~SkipList() {
  SkipNode<T> *cur = head_;
  SkipNode<T> *next;
  while (cur != nullptr) {
    next = cur->nodes[0];
    delete cur;
    cur = next;
  }
}

//traverse begin with the second node after the head node and delete each node
template<typename T>
void SkipList<T>::clear() {
  //begin from next node after head
  SkipNode<T> *cur = head_->nodes[0];
  SkipNode<T> *next;
  while (cur != nullptr) {
    next = cur->nodes[0];
    delete cur;
    cur = next;
  }
  for (int i = 0; i <= head_->getNodeHeight(); ++i) {
    head_->nodes[i] = nullptr;
  }
}

//traverse from highest to lowest linked list to search data
template<typename T>
SkipNode<T> *SkipList<T>::search(const T &data) const {
  SkipNode<T> *cur = head_;
  int height;
  for (height = cur_height_; height >= 0; --height) {
    while (cur->nodes[height] != nullptr and *(cur->nodes[height]->getData()) <= data)
      cur = cur->nodes[height];
    if (cur != head_ && *(cur->getData()) == data)
      return cur;
  }
  return nullptr;
}

//remove data from SkipList,
template<class T>
bool SkipList<T>::remove(const T &data) {
  SkipNode<T> *cur = head_;
  SkipNode<T> *pre[cur_height_ + 1];
  int height;

  //find the predecessors of the node to be removed
  for (height = cur_height_; height >= 0; --height) {
    while (cur->nodes[height] != nullptr and *(cur->nodes[height]->getData()) < data)
      cur = cur->nodes[height];
    pre[height] = cur;
  }
  cur = cur->nodes[0];

  //return false if the node to be removed does not exist
  if (cur == nullptr || *(cur->getData()) != data) {
    return false;
  }

  //fix the links and remove the node
  for (height = 0; height <= cur_height_; ++height) {
    if (pre[height]->nodes[height] != cur)
      break;
    pre[height]->nodes[height] = cur->nodes[height];
  }
  delete cur;

  //if the removed node was the only node at same level then fix the current height of the skip list
  while(head_->nodes[cur_height_--]==nullptr)
    ;
  return true;
}

template<typename T>
void SkipList<T>::insert(const T &data) {
  SkipNode<T> *pre[max_height_ + 1];
  SkipNode<T> *cur = head_;
  int height;

  /* find the predecessors of the inserted data */
  for (height = cur_height_; height >= 0; --height) {
    while (cur->nodes[height] != nullptr && *(cur->nodes[height]->getData()) < data)
      cur = cur->nodes[height];
    //store predecessor of height
    pre[height] = cur;
  }

  int level = random_->getRandomLevel();
  SkipNode<T> *node = new SkipNode<T>(data, level);
  //更新了level
  if (level > cur_height_) {
    //将(cur_height_,level]之间的pre,即新node的上一个节点设置为head结点
    for (height = level; height > cur_height_; --height) {
      pre[height] = head_;
    }
    //update curent height
    cur_height_ = level;
  }

  //set the proper links at each level
  for (height = level; height >= 0; --height) {
    node->nodes[height] = pre[height]->nodes[height];
    //connect pre node to new node build here
    pre[height]->nodes[height] = node;
  }
}

namespace zy {

template
class SkipList<int>;

}

