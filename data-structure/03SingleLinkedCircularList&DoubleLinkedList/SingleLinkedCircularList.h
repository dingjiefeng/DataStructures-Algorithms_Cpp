//
// Created by djf on 2016/12/21 0021.
//

#ifndef INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_SINGLELINKEDCIRCULARLIST_H
#define INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_SINGLELINKEDCIRCULARLIST_H

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
class SingleLinkedCircularList: public LinearList<T> {
public:
    class iterator{
    public:
        //
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

    protected:
        chainNode<T>* node;
    };
    iterator begin(){ return iterator(headerNode->next->element);}
    iterator end(){ return iterator(headerNode->element);}
public:
    //construct copy destroy
    SingleLinkedCircularList(): listSize(0) { headerNode = new chainNode<T>(); headerNode->next = headerNode;}
    SingleLinkedCircularList(const SingleLinkedCircularList& );
    ~SingleLinkedCircularList();
    //ADT
    bool empty() const override;
    int size() const override ;
    T& get(int index) const override ;
    int indexof(const T& theElement) const override ;
    void erase(int index) override ;
    void insert(int index,const T& theElement) override ;
    void output(ostream& out) const override ;
    //extend
    void clear() override ;
    void push_back(const T& theElement) override ;
protected:
    void checkIndex(int index) const;
    chainNode<T>* headerNode;
    int listSize;
};

template <typename T>
SingleLinkedCircularList<T>::SingleLinkedCircularList(const SingleLinkedCircularList &S)
{
    chainNode<T>* currNode = headerNode;
    chainNode<T>* currS = S.headerNode;
    while(currS->next!=S.headerNode)
    {
        currNode->next = new chainNode<T>(currS->next->element);
        currNode = currNode->next;
        currS = currS->next;
    }
    currNode->next = headerNode;
    listSize = S.listSize;
}

template <typename T>
SingleLinkedCircularList<T>::~SingleLinkedCircularList()
{
    chainNode<T>* currNode = headerNode->next;
    while(headerNode->next != headerNode)
    {
        headerNode->next = currNode->next;
        delete currNode;
        currNode = headerNode->next;
    }
}
template <typename T>
bool SingleLinkedCircularList<T>::empty() const
{
    return headerNode->next==headerNode;
}

template <typename T>
int SingleLinkedCircularList<T>::size() const
{
    return listSize;
}

template <typename T>
void SingleLinkedCircularList<T>::checkIndex(int index) const
{
    if(index<0 || index>listSize)
    {
        cerr << "----! index outrange!----" << endl;
    }
}

template <typename T>
T &SingleLinkedCircularList<T>::get(int index) const
{
    checkIndex(index);
    chainNode<T>* currNode = headerNode->next;
    for(int i = 0;i<index;++i)
    {
        currNode = currNode->next;
    }
    return currNode->element;
}

template <typename T>
int SingleLinkedCircularList<T>::indexof(const T &theElement) const
{
    chainNode<T>* currNode = headerNode->next;
    int i = 0;
    while(currNode->next != headerNode)
    {
        currNode = currNode->next;
        if(currNode->element==theElement)
            return i;
        ++i;
    }
    return -1;
}

template <typename T>
void SingleLinkedCircularList<T>::erase(int index)
{
    checkIndex(index);
    chainNode<T>* currNode = headerNode->next;
    for(int i = 0;i<index-1;++i)
        currNode = currNode->next;
    chainNode<T>* tmp = currNode->next;
    currNode->next = currNode->next->next;
    delete tmp;
    --listSize;
}

template <typename T>
void SingleLinkedCircularList<T>::insert(int index, const T &theElement)
{
    checkIndex(index);
    chainNode<T>* currNode = headerNode->next;
    for(int i=0;i<index;++i)
        currNode = currNode->next;
    currNode->next = new chainNode<T>(theElement,currNode->next->next);
    ++listSize;
}

template <typename T>
void SingleLinkedCircularList<T>::output(ostream &out) const
{
    chainNode<T>* currNode = headerNode->next;
    while(currNode!=headerNode)
    {
        out << currNode->element << " ";
        currNode = currNode->next;
    }
}

template <typename T>
void SingleLinkedCircularList<T>::clear()
{
    chainNode<T>* currNode = headerNode->next;
    while(currNode!=headerNode)
    {
        headerNode->next = headerNode->next->next;
        delete currNode;
        currNode = headerNode->next;
    }
    listSize = 0;
}

template <typename T>
void SingleLinkedCircularList<T>::push_back(const T &theElement)
{
    headerNode->next = new chainNode<T>(theElement,headerNode->next);
    ++listSize;
}


#endif //INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_SINGLELINKEDCIRCULARLIST_H
