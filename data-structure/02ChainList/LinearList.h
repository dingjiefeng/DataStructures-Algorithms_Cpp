//
// Created by djf on 2016/12/18 0018.
//

#ifndef INC_01_ARRAYLIST_LINEARLIST_H
#define INC_01_ARRAYLIST_LINEARLIST_H

#include <iostream>
template <typename T>
class LinearList {
public:
    virtual ~LinearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int index) const = 0;
    virtual int indexof(const T& theElement) const = 0;//first pos
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T& theElement) = 0;
    virtual void output(std::ostream& out) const = 0;
    //extend
    virtual void clear() = 0;
    virtual void push_back(const T& theElement)  = 0;
};


#endif //INC_01_ARRAYLIST_LINEARLIST_H
