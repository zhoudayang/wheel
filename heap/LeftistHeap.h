//
// Created by zhouyang on 2016/10/24.
//

#ifndef HEAP_LEFTISTHEAP_H
#define HEAP_LEFTISTHEAP_H

#include <algorithm>

template<typename Comparable>
class LeftistHeap {
public:
    LeftistHeap():root{nullptr}{

    }
    LeftistHeap(const LeftistHeap &rhs):
            root(nullptr){
        //clone tree
        root = clone(rhs.root);
    }

    LeftistHeap(LeftistHeap && rhs):root{rhs.root}{
        rhs.root = nullptr;
    }

    ~LeftistHeap(){
        makeEmpty();
    }

    LeftistHeap & operator =(LeftistHeap &rhs){
        LeftistHeap copy = rhs;
        std::swap(*this,copy);
        return *this;
    }

    LeftistHeap &operator =(LeftistHeap &&rhs){
        std::swap(root,rhs.root);
        return *this;
    }

    bool isEmpty() const{
        return root == nullptr;
    }

    //return root value
    const Comparable &findMin() const{
        if(isEmpty())
            throw;
        return root->element;
    }

    //merge new tree with single node x
    void insert(const Comparable &x){
        root = merge(new LeftistNode{x},root);
    }

    //merge new tree with single node x
    void insert(Comparable &&x){
        root = merge(new LeftistNode{std::move(x)},root);
    }

    void deleteMin(){
        if(isEmpty())
            throw;
        LeftistNode * oldRoot = root;
        //merge left child tree and right child tree
        root = merge(root->left,root->right);
        delete oldRoot;
    }

    //get min element and delete it from tree
    void deleteMin(Comparable &minItem){
        minItem = findMin();
        deleteMin();
    }


    //clear tree
    void makeEmpty(){
        reclaimMemory(root);
        root = nullptr;
    }

    //merge with rhs
    void merge(LeftistHeap & rhs){
        if(this == &rhs)
            return;
        root = merge(root,rhs.root);
        rhs.root = nullptr;
    }
private:
    struct LeftistNode {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const Comparable &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0) :
                element(e), left(lt), right(rt), npl(np) {

        }

        LeftistNode(Comparable &&e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0) :
                element(std::move(e)), left(lt), right(rt), npl(np) {

        }
    };

    LeftistNode *root;

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        //make first parameter smaller than second parameter
        if (h1->element < h2->element)
        {
            return merge1(h1, h2);
        }
        return merge1(h2, h1);
    }

    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2) {
        //if left child of h1 is empty, set h2 as left child of h1
        if (h1->left == nullptr)
            h1->left = h2;
        else
        {
            //merge right child of h1 and h2
            h1->right = merge(h1->right, h2);
            //make left child tree 's npl smaller than right child tree
            if (h1->left->npl < h1->right->npl)
                swapChildren(h1);
            //update h1's npl
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    //swap children
    void swapChildren(LeftistNode *root ){
        std::swap(root->left,root->right);
    }

    //递归删除
    void reclaimMemory(LeftistNode *t) {
        if (t != nullptr)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }

    LeftistNode * clone(LeftistNode *root){
        if(root == nullptr)
            return nullptr;
        return new LeftistNode(root->element,clone(root->left),clone(root->right),root->npl);
    }
};


#endif //HEAP_LEFTISTHEAP_H
