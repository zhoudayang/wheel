#pragma once

#include <experimental/optional>

namespace zy{

// 使用自定义比较，定义在MyComparable, 必须实现 == 以及 < operator
template<typename Key>
class MyComparable
{
 public:
  bool equal(const Key& lhs, const Key& rhs) const { return lhs == rhs; }
  bool less(const Key& lhs, const Key& rhs) const { return lhs < rhs; }
};

template<typename Key, typename Value, typename Comparable = MyComparable<Key>>
class RedBlackTree
{
  public:
    RedBlackTree()
      : root_(nullptr)
    { }

    // get value of given key, simple binary search
    std::experimental::optional<Value> get(Key key) const
    {
      Node* x = root_;
      while(x != nullptr)
      {
        if(comparable.equal(key, x->key))
          return { x->value };
        else if(comparable.less(key, x->key))
          x = x->left;
        else
          x = x->right;
      }
      return {};
    }

    // put <key, value> into tree
    void put(Key key, Value value)
    {
      root_ = insert(root_, key, value);
      root_->color = Color::BLACK;
    }

  int size() const { if(root_ == nullptr) return 0; else return root_->size(); }

  void deleteMax()
  {
    root_ = deleteMax(root_);
    if(root_)
      root_->color = Color::BLACK;
  }

  void deleteMin()
  {
    root_ = deleteMin(root_);
    if(root_)
      root_->color = Color::BLACK;
  }

  void deleteNode(Key key)
  {
    root_ =  deleteNode(root_, key);
    if(root_)
      root_->color = Color::BLACK;
  }

 private:
    // use enum class to identity color
    enum class Color
    {
      RED,
      BLACK
    };

    struct Node
    {
      // three constructor
      Node(Key key, Value val, Color color)
        : key(key), value(val), color(color), left(nullptr), right(nullptr), size_(1)
      { }

      Node(Key key, Value val, Color color, Node* left, Node* right)
        : key(key), value(val), color(color), left(left), right(right), size_(1)
      { }

      Node(Key key, Value val)
        : key(key), value(val), color(Color::RED), left(nullptr), right(nullptr), size_(1)
      { }

      void flipColor() {
        if(color == Color::RED)
          color = Color::BLACK;
        else
          color = Color::RED;
      }

      int size() const { return size_; }

      Key key;
      Value value;
      Color color;
      Node* left;
      Node* right;

      int size_; // number of nodes in tree rooted here
    };

    Node* root_;
    Comparable comparable;

  private:

    Node* rotateLeft(Node* h)
    {
      Node* temp = h->right;
      h->right = temp->left;
      temp->left = setSize(h);
      temp->color = temp->left->color;
      temp->left->color = Color::RED;
      return setSize(temp);
    }

    Node* rotateRight(Node* h)
    {
      Node* temp = h->left;
      h->left = temp->right;
      temp->right = setSize(h);
      temp->color = temp->right->color;
      temp->right->color = Color::RED;
      return setSize(temp);
    }

    Node* colorFlip(Node* h)
    {
      h->flipColor();
      if(h->left)
        h->left->flipColor();
      if(h->right)
        h->right->flipColor();
      return h;
    }

    // leaf node is black node
    bool isRed(Node* h) {
      if(h == nullptr)
        return false;
      else
      {
        return h->color == Color::RED;
      }
    }

    Node* insert(Node* h, Key key, Value val)
    {
      if(h == nullptr)
        return new Node(key, val);

      if(isRed(h->left) && isRed(h->right))
      {
        colorFlip(h);
      }

      if(comparable.equal(key, h->key))
      {
        h->value = val;
      }
      else if(comparable.less(key, h->key))
      {
        h->left = insert(h->left, key, val);
      }
      else
      {
        h->right = insert(h->right, key, val);
      }

      if(isRed(h->right))
      {
        h = rotateLeft(h);
      }
      if(isRed(h->left) && isRed(h->left->left))
      {
        h = rotateRight(h);
      }
      return setSize(h);
    }

    Node* fixUp(Node* h)
    {
      if(isRed(h->right))                        // rotate-left right-learning reds
      {
        h = rotateLeft(h);
      }
      if(isRed(h->left) && isRed(h->left->left)) // rotate-right red-red pairs
      {
        h = rotateRight(h);
      }
      if(isRed(h->left) && isRed(h->right))      // split 4 nodes
      {
        colorFlip(h);
      }
      return setSize(h);
    }

    Node* moveRedRight(Node* h)
    {
      colorFlip(h);
      // now h->left and h->right is red
      if(h->left && isRed(h->left->left))
      {
        h = rotateRight(h);
        colorFlip(h);
      }
      return h;
    }

    Node* deleteMax(Node* h)
    {
      if(isRed(h->left))                                // lean 3-nodes to the right
        h = rotateRight(h);
      if(h->right == nullptr)                          // move node on bottom level(h must be red)
      {
        return nullptr;
      }
      if(h->right && !isRed(h->right) && !isRed(h->right->left))
      {
        h = moveRedRight(h);
      }
      h->right = deleteMax(h->right);
      return fixUp(h);                                  // fix right-leaning red links and eliminate 4-nodes on the way up
    }

    Node* moveRedLeft(Node* h)
    {
      colorFlip(h);
      if(h->right && isRed(h->right->left))
      {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
        colorFlip(h);
      }
      return h;
    }

    Node* deleteMin(Node* h)
    {
      if(h->left == nullptr)        // remove node on bottom level (h must be RED by invariant)
        return nullptr;            // push red link down if necessary
      if(h->left && !isRed(h->left) && !isRed(h->left->left))
      {
        h = moveRedLeft(h);         // push red link down if necessary
      }
      h->left = deleteMin(h->left); // move down one level
      return fixUp(h);              // fix right-leaning red links and eliminate 4-nodes on the way up
    }

    Node* deleteNode(Node* h, Key key)
    {
      if(h == NULL)
        return nullptr;
      if(comparable.less(key, h->key))                 // left
      {
        if(h->left && !isRed(h->left) && !isRed(h->left->left))   // push red right if necessary
        {
          h = moveRedLeft(h);                          // move down left
        }
        h->left = deleteNode(h->left, key);
      }
      else // right or equal
      {
        if(isRed(h->left))
        {
          h = rotateRight(h);
        }
        if(comparable.equal(h->key, key) && h->right == nullptr) // equal at bottom delete node
          return nullptr;
        if(h->right && !isRed(h->right) && !isRed(h->right->left))
          h = moveRedRight(h);
        if(comparable.equal(h->key, key))
        {
          Node* min_node = getMin(h->right);
          h->value = min_node->value;
          h->key = min_node->key;
          h->right = deleteMin(h->right);
        }
        else
          h->right = deleteNode(h->right, key);
      }
      return fixUp(h);
    }

    // get minimum node of tree h
    Node* getMin(Node* h) const
    {
      if(h->left == nullptr)
        return h;
      else
        return getMin(h->left);
    }

    static int size(Node* h) { if(h == nullptr) return 0; else return h->size(); }

    static Node* setSize(Node* h) { h->size_ = size(h->left) + size(h->right) + 1; return h; }
 };
}