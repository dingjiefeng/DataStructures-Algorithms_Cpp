//
// Created by djf on 2016/12/18 0018.
//

#ifndef INC_01_ARRAYLIST_ARRAYLIST_H
#define INC_01_ARRAYLIST_ARRAYLIST_H

#include "LinearList.h"
#include <iterator>
#include <algorithm>
using namespace std;

template <typename T> void resizeCapacity(T*& a,int oldCapacity, int newCapacity);

template <typename T>
class ArrayList :public LinearList<T> {
public:
    //iterator
    class iterator{
    public:
        //
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        //construct
        iterator(T* thepos=0) { pos = thepos;}
        //operator
        T& operator*() const { return *pos;}
        T* operator->() const { return &*pos;}
        iterator& operator++()
            { ++pos; return *this;}
        iterator& operator++(int)
            { iterator old = *this; ++pos; return old;}
        iterator& operator--()
            { --pos; return *this;}
        iterator& operator--(int)
            { iterator old = *this; --pos; return old;}
        bool operator!=(const iterator rhl) const
            { return pos != rhl.pos;}
        bool operator==(const iterator rhl) const
            { return pos == rhl.pos;}
    protected:
        T* pos;
    };
    iterator begin(){ return iterator(element);}
    iterator end(){ return iterator(element+listsize);}
public:
    //construct copy destroy
    //ArrayList(int initCapacity = 10);
    ArrayList(int initCapacity = 10, int size = 0);
    ArrayList(const ArrayList<T>&);
    ~ArrayList() { delete [] element;};
    //ADT methods
    bool empty() const override { return listsize==0;}
    int size() const override { return listsize;}
    T& get(int index) const override;
    int indexof(const T& theElement) const override ;
    void erase(int index) override ;
    void insert(int index, const T& theElement) override ;
    void output(ostream& out) const override ;
    //other
    int capacity() const { return arrayCapacity;}
    void set(int index, T var);
    void trimToSize();
    void setSize(int setSize);
    T& operator[](int);
    bool const operator==(const ArrayList &);
    bool const operator!=(const ArrayList &);
    bool const operator<(const ArrayList &);

protected:
    void checkIndex(int index) const;
    T* element;
    int arrayCapacity;
    int listsize;
    int addsize;
};
template <typename T>
ostream& operator<<(ostream& out,ArrayList<T>& al);


template <typename T>
ArrayList<T>::ArrayList(int initCapacity,int size)
{
    if (initCapacity < 0 || size<0)
    {
        std::cerr << "----!Initdata error!----" << std::endl;
    }
    arrayCapacity = initCapacity;
    listsize = 1;
    element = new T[arrayCapacity];
    addsize = size;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &rhl)
{
    arrayCapacity = rhl.arrayCapacity;
    listsize = rhl.listsize;
    delete [] element;
    element = new T[arrayCapacity];
    copy(rhl.element,rhl.element+listsize,element);
}

template <typename T>
void ArrayList<T>::checkIndex(int index) const
{
    if (index < 0 || index >= listsize)
    {
        cerr << "----!Index outrange!----" << endl;
    }
}

template <typename T>
T &ArrayList<T>::get(int index) const
{
    checkIndex(index);
    return element[index];
}

template <typename T>
int ArrayList<T>::indexof(const T &theElement) const
{
    int pos = find(element,element+listsize,theElement)-element;
    if (pos==listsize)
        return -1;
    return pos;
}

template <typename T>
void ArrayList<T>::erase(int index)
{
    checkIndex(index);
    copy(element+index+1,element+listsize,element+index);
    element[--listsize].~T();
    if(arrayCapacity>4*listsize)
    {
        for(int i = 4*listsize;i<arrayCapacity;++i)
            element[i].~T();
        arrayCapacity = 4*listsize;
    }
}

template <typename T>
void ArrayList<T>::insert(int index, const T &theElement)
{
    ++listsize;
    checkIndex(index);
    if(listsize>=arrayCapacity)
    {
        if(addsize==0)
        {
            resizeCapacity(element, arrayCapacity, arrayCapacity * 2);
            arrayCapacity *= 2;
        }
        else
        {
            resizeCapacity(element, arrayCapacity, arrayCapacity + addsize);
            arrayCapacity += addsize;
        }
    }
    copy(element+index,element+listsize-1,element+index+1);
    element[index] = theElement;
}

template <typename T>
void ArrayList<T>::output(ostream &out) const
{
    copy(element,element+listsize,ostream_iterator<T>(out," "));
}

template <typename T>
void ArrayList<T>::set(int index, T var)
{
    checkIndex(index);
    element[index] = var;
}

template <typename T>
void ArrayList<T>::trimToSize()
{
    int edge = max(1,listsize);
    for(int i = edge+1;i<arrayCapacity;i++)
        element[i].~T();
    arrayCapacity = listsize;
}

template <typename T>
void ArrayList<T>::setSize(int setSize)
{
    if(setSize<listsize)
        cerr << "----!setSize must be >= listsize !----";
    if(setSize<=arrayCapacity)
    {
       for(int i = setSize+1;i<arrayCapacity;++i)
           element[i].~T();
        arrayCapacity = setSize;
    } else
    {
        T* tmp = new T[setSize];
        copy(element,element+listsize,tmp);
        delete [] element;
        element = tmp;
    }
}

template <typename T>
T &ArrayList<T>::operator[](int index)
{
    checkIndex(index);
    return element[index];
}

template <typename T>
bool const ArrayList<T>::operator==(const ArrayList &rhl)
{
    if(listsize!=rhl.listsize)
        return 0;
    else
    {
        for(int i = 0;i<listsize;++i)
        {
            if(element[i]!=rhl.element[i])
                return 0;
        }
    }
    return true;
}

template <typename T>
bool const ArrayList<T>::operator!=(const ArrayList &rhl)
{
    return !(*this==rhl);
}

template <typename T>
bool const ArrayList<T>::operator<(const ArrayList &rhl)
{
    int index = min(listsize,rhl.listsize);
    for(int i = 0;i<index;++i)
    {
        if(element[i]>=rhl.element[i])
            return 0;
    }
    if(listsize<rhl.listsize)
        return 1;
    else
    {
        return 0;
    }

}

template<typename T>
ostream &operator<<(ostream &out, ArrayList<T> &al)
{
    al.output(out);
    return out;
}

template <typename T>
void resizeCapacity(T*& a,int oldCapacity, int newCapacity)
{
    if(newCapacity<0)
    {
        cerr << "----!newCapacity must be>=0!----";
    }
    T* tmp = new T[newCapacity];
    int num = min(oldCapacity,newCapacity);
    copy(a,a+num,tmp);
    delete [] a;
    a = tmp;
}

#endif //INC_01_ARRAYLIST_ARRAYLIST_H
