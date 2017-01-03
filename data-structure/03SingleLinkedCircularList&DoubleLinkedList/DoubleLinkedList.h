//
// Created by djf on 2016/12/21 0021.
//

#ifndef INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_DOUBLELINKEDLIST_H
#define INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_DOUBLELINKEDLIST_H

#include "LinearList.h"

using namespace std;

template <typename T>
struct doubleChainNode{
    T element;
    doubleChainNode<T>* next;
    doubleChainNode<T>* previous;
    doubleChainNode() {}
    doubleChainNode(const T& e) { this->element = e;}
    doubleChainNode(const T& e, doubleChainNode<T>* p,doubleChainNode<T>* n)
        { this->element=e;this->previous=p;this->next=n;}
};

template <typename T>
class DoubleLinkedList: public LinearList<T> {
public:
    class iterator{

    };
public:
    //construct copy destroy
    DoubleLinkedList():listSize()
    { headerNode = new doubleChainNode<T>();headerNode->next=headerNode;headerNode->previous=headerNode;}
    DoubleLinkedList(const DoubleLinkedList& D);
    ~DoubleLinkedList();
    //ADT
    bool empty() const override ;
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
    void checkIndex(int index);
    int listSize;
    doubleChainNode<T>* headerNode;
};

template <typename T>
void DoubleLinkedList::checkIndex(int index)
{
    if(index<0 || index>listSize)
        cerr << "----! index outrange !----" << endl;
}


#endif //INC_03_SINGLELINKEDCIRCULARLIST_DOUBLELINKEDLIST_DOUBLELINKEDLIST_H
