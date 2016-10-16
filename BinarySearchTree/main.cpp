#include "tree.h"

#include <iostream>

using namespace std;

class object {
public:
    object(int val)
            :val_(val)
    {
       // cout << "object constructor" << endl;
    }

    object(const object& other)
            :val_(other.val_)
    {
       // cout << "copy constructor" << endl;
    }

    object(object&& other)
            :val_(std::move(other.val_))
    {
        //cout << "move copy construstor" << endl;
    }

    bool operator <(const object & other) const{
        return val_<other.val_;
    }
    bool operator >(const object & other) const{
        return val_ > other.val_;
    }
    object& operator=(const object& rhs)
    {
        val_ = rhs.val_;
       // cout<<"normal copy assignment function"<<endl;
        return *this;
    }

    object operator =(object &&rhs){
        val_ = std::move(rhs.val_);
        //cout<<"copy assignment function with moving semantic";
        return * this;
    }

    ~object(){
       // cout<<"destructor"<<endl;
    }


private:
    int val_;

    friend std::ostream & operator <<(std::ostream & out,const object & x);
};

std::ostream & operator <<(std::ostream &out,const object &x){
    out<<x.val_;
    return out;
}

int main()
{
    BinarySearchTree<object> tree;
    for(int i=0;i<1;i++){
        tree.insert(object(rand()));
    }
    tree.printTree();
    tree.makeEmpty();

    for(int i=0;i<100;i++)
        tree.insert(object(i));
    tree.remove(0);

    cout<<tree.findMin()<<endl;
    cout<<tree.findMax()<<endl;
    tree.insert(101);
    cout<<tree.findMax()<<endl;
    auto other = tree ;
    cout<<other.findMax()<<endl;
    cout<<other.findMin()<<endl;

    return 0;
}