//
// Created by fit on 16-10-16.
//

#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

template<typename Comparable>
class AvlTree {
public:
    AvlTree()
            :root(nullptr)
    {

    }

    AvlTree(const AvlTree& rhs)
            :root(nullptr)
    {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree&& rhs)
            :root(rhs.root)
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    AvlTree& operator=(const AvlTree& rhs)
    {
        //调用复制构造函数
        AvlTree copy = rhs;
        //调用移动赋值函数
        std::swap(*this, copy);
        return *this;
    }

    AvlTree& operator=(AvlTree&& rhs)
    {
        std::swap(rhs.root, root);
        return *this;
    }

    const Comparable& findMin() const
    {
        if (isEmpty())
        {
            throw;
        }
        return findMin(root)->element;
    }

    const Comparable& findMax() const
    {
        if (isEmpty())
            throw;
        return findMax(root)->element;
    }

    bool contains(const Comparable& x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root==nullptr;
    }

    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(const Comparable& x)
    {
        insert(x, root);
    }

    void insert(Comparable&& x)
    {
        insert(std::move(x), root);
    }

    void remove(const Comparable& x)
    {
        remove(x, root);
    }
private:
    struct AvlNode {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const Comparable& elem, AvlNode* left_ptr, AvlNode* right_ptr, int h = 0)
                :element(elem),
                 left(left_ptr),
                 right(right_ptr),
                 height(h)
        {

        }
        AvlNode(Comparable&& elem, AvlNode* left_ptr, AvlNode* right_ptr, int h = 0)
                :element(std::move(elem)),
                 left(left_ptr),
                 right(right_ptr),
                 height(h)
        {

        }
    };

    //最大允许的左右子树的高度差
    static const int ALLOWED_IMBALANCE = 1;

    AvlNode* root;

    void insert(const Comparable& x, AvlNode*& t)
    {
        if (t==nullptr)
            t = new AvlNode(x, nullptr, nullptr);
        else if (x<t->element)
            insert(x, t->left);
        else if (t->element<x)
            insert(x, t->right);
        //re balance the tree
        balance(t);
    }

    void insert(Comparable&& x, AvlNode*& t)
    {
        if (t==nullptr)
            t = new AvlNode(std::move(x), nullptr, nullptr);
        else if (x<t->element)
            insert(x, t->left);
        else if (t->element<x)
            insert(x, t->right);
        //re blance the tree
        balance(t);
    }

    void remove(const Comparable& x, AvlNode*& t)
    {
        if (t==nullptr)
            return;
        if (x<t->element)
            remove(x, t->left);
        else if (t->element<x)
            remove(x, t->right);
        else if (t->left!=nullptr && t->right!=nullptr)
        {
            //将右子树的最小值赋值给t
            t->element = findMin(t->right)->element;
            //删除右子树中对应的最小值
            remove(t->element, t->right);
        }
        else
        {
            AvlNode* oldNode = t;
            t = (t->left!=nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    //todo
    void balance(AvlNode*& t)
    {
        if (t==nullptr)
            return;
        if (height(t->left)-height(t->right)>ALLOWED_IMBALANCE)
        {
            if (height(t->left->left)>=height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if (height(t->right)-height(t->left)>ALLOWED_IMBALANCE)
        {
            if (height(t->right->right)>=height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = max(height(t->left), height(t->right))+1;
    }

    AvlNode* findMin(AvlNode* t) const
    {
        if (t==nullptr)
            return nullptr;
        if (t->left==nullptr)
            return t;
        return findMin(t->left);
    }

    AvlNode* findMax(AvlNode* t) const
    {
        if (t!=nullptr)
            while (t->right!=nullptr)
                t = t->right;
        return t;
    }

    bool contains(const Comparable& x, AvlNode* t) const
    {
        if (t==nullptr)
            return false;
        else if (x<t->element)
            return contains(x, t->left);
        else if (t->element<x)
            return contains(x, t->right);
        return true;
    }

    void makeEmpty(AvlNode* t)
    {
        if (t!=nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    // 简单的中序遍历
    void printTree(AvlNode * t) const{
        if(t!=nullptr){
            printTree(t->left);
            cout<<t->element<<endl;
            printTree(t->right);
        }
    }

    //简单的先序遍历
    AvlNode * clone(AvlNode * t) const{
        if(t==nullptr)
            return nullptr;
        else
            return new AvlNode(t->element,clone(t->left),clone(t->right));
    }

    int height(AvlNode * t) const{
        return t==nullptr? -1:t->height;
    }

    int max(int lhs,int rhs) const{
        return lhs>rhs?lhs:rhs;
    }

    ///todo: check it
    void rotateWithLeftChild(AvlNode * & k2){
        AvlNode * k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right)) +1;
        k1->height = max(height(k1->left),k2->height) +1;
        k2 = k1;
    }

    void rotateWithRightChild(AvlNode * & k1){
        AvlNode * k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left),height(k1->right))+1;
        k2->height = max(height(k2->right),k1->height)+1;
        k1=k2;
    }

    void doubleWithLeftChild(AvlNode * & k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode * & k1){
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

};

#endif //VECTOR_AVLTREE_H
