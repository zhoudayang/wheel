//
// Created by zhouyang on 16-10-12.
//

#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H

#include <algorithm>

template<typename Object>
class List {
private:
    struct Node {
        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
                : data(d),
                  prev(p),
                  next(n) {

        }

        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
                : data(d),
                  prev(p),
                  next(n) {
//
        }

        //data
        Object data;
        //prev pointer
        Node *prev;
        //next pointer
        Node *next;

    };

public:

    class const_iterator {
    public:
        const_iterator()
                : current(nullptr) {}

        //解引用
        Object &operator*() const {
            return retrieve();
        }

        const Object *operator->() const {
            return retriveAsPtr();
        }

        const_iterator &operator++() {
            current = current->next;
            return *this;
        }


        //返回的是局部变量，不能为引用类型
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator &operator--() {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node *current;

        Object &retrieve() const {
            return current->data;
        }

        Object *retriveAsPtr() const {
            return &(current->data);
        }

        const_iterator(Node *p)
                : current(p) {}

        //使得List<Object>可以访问protected作用域下的构造函数
        friend class List<Object>;
    };

    class iterator : public const_iterator {
    public:
        iterator() {}

        Object &operator*() {
            return const_iterator::retrieve();
        }

        Object *operator->() {
            return const_iterator::retriveAsPtr();
        }

        iterator operator++() {
            this->current = this->current->next;
            return *this;
        }

        //返回的是局部变量，不能为引用类型
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--() {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }

    protected:
        iterator(Node *p)
                : const_iterator(p) {}

        friend class List<Object>;
    };

    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

    List() {
        init();
    };

    List(const List &rhs) {
        init();
        //这里有一个auto调用
        for (auto &x:rhs)
        {
            push_back(x);
        }
    }

    List(List &&rhs)
            : theSize(rhs.theSize),
              head(rhs.head),
              tail(rhs.tail) {
        theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    ~List() {
        clear();
        delete head;
        delete tail;
    }

    List &operator=(const List &rhs) {
        List copy = rhs;
        std::swap(copy, rhs);
        return *this;
    }

    List &operator=(List &&rhs) {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }

    iterator begin() {
        return {head->next};
    }

    const_iterator begin() const {
        return {head->next};
    }

    iterator end() {
        return {tail};
    }

    const_iterator end() const {
        return {tail};
    }

    int size() const {
        return theSize;
    }

    bool empty() const {
        return size() == 0;
    }

    void clear() {
        while (!empty())
        {
            pop_front();
        }
    }

    Object &front() {
        return *begin();
    }

    const Object &front() const {
        return *begin();
    }

    Object &back() {
        return *--end();
    }

    const Object &back() const {
        return *--end();
    }

    void push_front(const Object &x) {
        insert(begin(), x);
    }

    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x) {
        insert(end(), x);
    }

    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }

    //在it之前插入x
    iterator insert(iterator it, const Object &x) {
        Node *p = it.current;
        ++theSize;
        return {p->prev = p->prev->next = new Node(x, p->prev, p)};
    }

    iterator insert(iterator it, Object &&x) {
        Node *p = it.current;
        ++theSize;
        return {p->prev = p->prev->next = new Node(std::move(x), p->prev, p)};
    }

    //删除it对应的节点
    iterator erase(iterator it) {
        Node *p = it.current;
        iterator ret{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;
        return ret;
    }

    iterator erase(iterator from, iterator to) {
        //此处不能采取itr++, 因为在erase之后,itr就失效了
        for (iterator itr = from; itr != to;)
            itr = erase(itr);
        return to;
    }

private:
    int theSize;
    Node *head;
    Node *tail;

};

#endif //VECTOR_LIST_H
