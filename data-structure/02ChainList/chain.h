//
// Created by djf on 2016/12/20 0020.
//

#ifndef INC_02_CHAIN_CHAIN_H
#define INC_02_CHAIN_CHAIN_H

#include "LinearList.h"
using namespace std;
template <typename T>
struct chainNode{
    //data
    T element;
    chainNode<T> *next;
    //method
    chainNode() {}
    chainNode(const T& e) { this->element=e;}
    chainNode(const T& e, chainNode<T>* n) { this->element=e;this->next=n;}
};

template <typename T>
class chain: public LinearList<T> {
public:
    //one direction iterator
    class iterator{
    public:
        // typedefs required by C++ for a forward iterator
        typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        //construct
        iterator(chainNode<T>* theNode = nullptr) { node = theNode;}
        //operator
        T& operator*() const { return node->element;}
        T* operator&() const { return &node->element;}
        iterator& operator++() { node = node->next;return *this;}
        iterator operator++(int) { iterator old = *this; node = node->next; return old;}
        bool operator==(const iterator rhl) const { return node == rhl.node;}
        bool operator!=(const iterator rhl) const { return node != rhl.node;}
        //other

    protected:
        chainNode<T>* node;
    };
public:
    //consturct copy destory
    chain(int initCapacity=10);
    chain(const chain<T>&);
    ~chain();
    //ADT method from LinearList.h
    bool empty() const override { return listSize==0;};
    int size() const override { return listSize;}
    T& get(int index) const override;
    int indexof(const T&) const override;
    void erase(int index) override;
    void insert(int index,const T& theElement) override;
    void output(ostream& out) const override;
    void push_back(const T& theElement) override ;
    void clear() override ;
    //other
    void removeRange(int fromIndex,int toIndex);
    int lastIndexOf(const T& theElement);
    T& operator[](int index) const;
    void reverse();
protected:
    void checkIndex(int index) const;
    chainNode<T>* headNode;
    int listSize;

};

template <typename T>
void chain<T>::removeRange(int fromIndex, int toIndex)
{
    checkIndex(fromIndex);checkIndex(toIndex);
    if(toIndex<fromIndex)
    {
        cerr << "----! fromIndex must <= toIndex !----" << endl;
        return;
    }
    chainNode<T>* p = headNode;
    if(fromIndex!=0)
    {
        chainNode<T>* q;
        for(int i = 0;i<toIndex;++i)
        {
            if(i<fromIndex-1)
                p = p->next;
            else
            {
                q = p->next;
                p->next = q->next;
                delete q;
            }
        }
    } else
    {
        for(int i = 0;i<=toIndex;++i)
        {
            headNode = headNode->next;
            delete p;
            p = headNode;
        }
    }
}

template <typename T>
chain<T>::chain(int initCapacity)
{
    //chain中无capacity，这么写为了和LinearList兼容
    if(initCapacity<1)
        cerr << "----!initSize must be >=1 !----";
    listSize = 0;
    headNode = nullptr;
}

template <typename T>
chain<T>::chain(const chain<T> & theList)
{
    listSize = theList.listSize;
    if(listSize==0)
    {
        headNode = nullptr;
        return;
    }
    chainNode<T>* sourceNode = theList.headNode;
    headNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = headNode;
    while(sourceNode!= nullptr)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        targetNode = targetNode->next;
    }
    targetNode->next = nullptr;
}

template <typename T>
chain<T>::~chain()
{
    while(headNode!= nullptr)
    {
        chainNode<T>* nextNode = headNode->next;
        delete headNode;
        headNode = nextNode;
    }
}

template <typename T>
T &chain<T>::get(int index) const
{
    checkIndex(index);
    chainNode<T>* currNode = headNode;
    for(int i=0;i<index;++i)
        currNode = currNode->next;
    return currNode->element;
}

template <typename T>
void chain<T>::checkIndex(int index) const
{
    if(index<0 || index>=listSize)
    {
        cerr << "----! index outrange !----" << endl;
        return;
    }
}

template <typename T>
int chain<T>::indexof(const T & theElement) const
{
    chainNode<T>* currNode = headNode;
    for(int i = 0;i<listSize;++i)
    {
        if(currNode->element==theElement)
            return i;
        currNode = currNode->next;
    }
    return -1;
}

template <typename T>
void chain<T>::erase(int index)
{
    checkIndex(index);
    chainNode<T>* deleteNode;
    if(index==0)
    {
        deleteNode = headNode;
        headNode = headNode->next;
    } else
    {
        chainNode<T> *p = headNode;
        for(int i=0;i<index-1;++i)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next;
    }
    --listSize;
    delete deleteNode;
}

template <typename T>
void chain<T>::insert(int index, const T &theElement)
{
    if(index<0 || index>listSize)
    {
        cerr << "---! insert index error !----" << endl;
        return;
    }
    if(index ==0)
    {
        headNode = new chainNode<T>(theElement,headNode);
    } else
    {
        chainNode<T> *p = headNode;
        for (int i = 0; i < index - 1; ++i)
            p = p->next;
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template <typename T>
void chain<T>::output(ostream &out) const
{
    for(chainNode<T>* p = headNode;p != nullptr;p=p->next)
        out << p->element << " ";

}

template <typename T>
void chain<T>::push_back(const T &theElement)
{
    chainNode<T>* currNode = headNode;
    for(int i=0;i<listSize-1;++i)
        currNode = currNode->next;
    currNode->next = new chainNode<T>(theElement, nullptr);
    ++listSize;
}

template <typename T>
void chain<T>::clear()
{
    chainNode<T>* p;
    while(headNode!= nullptr)
    {
        p = headNode->next;
        delete headNode;
        headNode = p;
    }
    listSize = 0;
}

template <typename T>
int chain<T>::lastIndexOf(const T& theElement)
{
    int pos = -1;int i = 0;
    chainNode<T>* p = headNode;
    while (p != nullptr)
    {
        if (p->element == theElement)
            pos = i;
        else
        {
            ++i;
            p = p->next;
        }
    }
}

template <typename T>
T& chain<T>::operator[](int index) const
{
    checkIndex(index);
    chainNode<T>* currNode = headNode;
    for(int i = 0;i<index;++i)
        currNode = currNode->next;
    return currNode->element;
}

template <typename T>
void chain<T>::reverse()
{
    if(listSize==0 || listSize==1)
        return;
    else if(listSize == 2)
    {
        chainNode<T>* p = headNode;
        headNode = headNode->next;
        headNode->next = p;
        p->next = nullptr;
    }
    else
    {
        chainNode<T>* p = headNode;
        chainNode<T>* q = headNode->next;
        chainNode<T>* r = headNode->next->next;
        headNode->next = nullptr;
        while(r->next != nullptr)
        {
            q->next = p;
            p = q;
            q = r;
            r = r->next;
        }
        q->next = p;
        r->next = q;
        headNode = r;
    }

}

template <typename T>
ostream& operator<<(ostream& out, const chain<T> &a)
{
    a.output(out);
    return out;
}


#endif //INC_02_CHAIN_CHAIN_H
