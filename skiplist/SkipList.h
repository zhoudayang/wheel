//
// Created by zhouyang on 2016/10/31.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <memory>
#include <iostream>
#include <cassert>

#include "SkipNode.h"

namespace zy {

class RandomLevel;

template<typename T>
class SkipList {
 public:
  SkipList(int max_height, double probability);

  ~SkipList();

  void insert(const T &data);

  bool remove(const T &data);

  SkipNode<T> *search(const T &data) const;

  void clear();

  class const_iterator {
   public:
    const_iterator() : current(nullptr) {

    }

    T &operator*() const {
      return retrieve();
    }

    const T *operator->() const {
      return retrieveAsPtr();
    }

    const_iterator &operator++() {
      assert(this->current != nullptr);
      current = current->nodes[0];
      return *this;
    }

    const_iterator operator++(int) {
      assert(this->current != nullptr);
      const_iterator old = *this;
      ++(*this);
      return old;
    }

    bool operator==(const const_iterator &rhs) const {
      return current == rhs.current;
    }
    bool operator!=(const const_iterator &rhs) const {
      return current != rhs.current;
    }
   protected:
    T &retrieve() const {
      assert(current->getData() != nullptr);
      return *current->getData();
    }

    T *retrieveAsPtr() const {
      return current->getData();
    }

    const_iterator(SkipNode<T> *ptr) :
        current(ptr) {
    }

    SkipNode<T> *current;

    friend class SkipList<T>;
  };

  class iterator : public const_iterator {
   public:
    iterator() {}

    T &operator*() {
      return const_iterator::retrieve();
    }

    T *operator->() {
      return const_iterator::retrieveAsPtr();
    }

    iterator &operator++() {
      assert(this->current != nullptr);
      this->current = this->current->nodes[0];
      return *this;
    }

    iterator operator++(int) {
      assert(this->current != nullptr);
      iterator old = *this;
      this->current = this->current->nodes[0];
      return old;
    }

   protected:
    iterator(SkipNode<T> *ptr) : const_iterator(ptr) {}
    friend class SkipList<T>;
  };

  const_iterator begin() const {
    return {head_->nodes[0]};
  }

  const_iterator end() const {
    return {nullptr};
  }

  iterator begin() {
    return {head_->nodes[0]};
  }

  iterator end() {
    return {nullptr};
  }

 private:
  //No copying allowed
  SkipList(const SkipList &);
  void operator=(const SkipList &);

  int max_height_;
  int cur_height_;
  double probability_;
  std::shared_ptr<RandomLevel> random_;
  SkipNode<T> *head_;

  //typename must not be X, or else will shadows template parameter
  template<typename Y>
  friend std::ostream &operator<<(std::ostream &os, zy::SkipList<Y> &list);
};

template<typename T>
std::ostream &operator<<(std::ostream &os, zy::SkipList<T> &list) {
  SkipNode<T> *cur = list.head_->nodes[0];
  while (cur) {
    os << *(cur->getData()) << " ";
    cur = cur->nodes[0];
  }
  os << std::endl;
  return os;
}

}

#endif //SKIPLIST_SKIPLIST_H
