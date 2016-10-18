#ifndef TREE_H

#include <algorithm>
#include <iostream>

//Comparable 可直接比较大小的数据类型

template<typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree()
            :root(nullptr)
    {

    }

    BinarySearchTree(const BinarySearchTree& rhs)
    {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree&& rhs)
            :root(rhs.root)
    {
        rhs.root = nullptr;
    }

    ~BinarySearchTree()
    {
        makeEmpty();
    }

    const Comparable& findMin() const
    {
        if(isEmpty())
            throw;
        return findMin(root)->element;

    }

    const Comparable& findMax() const
    {
        if(isEmpty())
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

    void printTree(std::ostream& out = std::cout) const{
        if(isEmpty()){
            out<<"Empty tree";
        }
        else
            printTree(root,out);
    }

    void makeEmpty(){
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

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs){
        std::swap(root,rhs.root);
        return * this;
    }

private:

    struct BinaryNode {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
                :element(theElement), left(lt), right(rt)
        {

        }

        BinaryNode(Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
                :element(std::move(theElement)), left(lt), right(rt)
        {

        }
    };


    BinaryNode* root;

    //使用的是指向指针的引用，这样可以将返回值写入t中
    void insert(const Comparable& x, BinaryNode*& t)
    {
        if (t==nullptr)
            t = new  BinaryNode(x, nullptr, nullptr);
        else if (x<t->element)
            insert(x, t->left);
        else if (t->element<x)
            insert(x, t->right);
        else
            //repeat situation, do nothing
            ;
    }

    void insert(Comparable&& x, BinaryNode*& t)
    {
        if (t==nullptr)
            t = new BinaryNode(std::move(x), nullptr, nullptr);
        else if (x<t->element)
            insert(std::move(x), t->left);
        else if (t->element<x)
            insert(std::move(x), t->right);
        else
            //do nothing
            ;
    }

    void remove(const Comparable& x, BinaryNode*& t)
    {
        if (t==nullptr)
            return;
        if (x<t->element)
            remove(x, t->left);
        else if (t->element<x)
            remove(x, t->right);
        else if (t->left && t->right)
        {
            //将右结点最小值赋给 t->element,然后从右子树中删除之前赋值的那个右子树中的那个结点
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* oldNode = t;
            //优先使用左结点代替t
            t = (t->left!=nullptr) ? t->left : t->right;
            //删除 oldNode
            delete oldNode;
        }
    }

    //recursie version
    BinaryNode* findMin(BinaryNode* t) const
    {
        if (t==nullptr)
            return nullptr;
        if (t->left==nullptr)
            return t;
        return findMin(t->left);
    }

    //common version
    BinaryNode* findMax(BinaryNode* t) const
    {
        if (t!=nullptr)
            while (t->right!=nullptr)
                t = t->right;
        return t;
    }

    /// binary search tree serach x, recursive way
    bool contains(const Comparable& x, BinaryNode* t) const
    {
        if (t==nullptr)
        {
            return false;
        }
        else if (x<t->element)
            return contains(x, t->left);
        else if (t->element<x)
            return contains(x, t->right);
        else
            return true;
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t!=nullptr)
        {
            //优先删除子节点
            makeEmpty(t->left);
            makeEmpty(t->right);
            //最后删除根节点
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode* t, std::ostream& out) const{
        if(t!=nullptr){
            printTree(t->left,out);
            out<<t->element<<std::endl;
            printTree(t->right,out);
        }
    }

    /// copy tree in recursive way
    BinaryNode* clone(BinaryNode* t) const
    {
        if (t==nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

};

#endif