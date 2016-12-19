#include <iostream>
#include "ArrayList.h"

template <typename T>
void resizeLength2D(T**& a,int oldRow,int oldCol,int newRow,int newCol)
{
    T** tmp = new T*[newRow];
    int r = min(oldRow,newRow);
    int c = min(oldCol,newCol);
    for(int i = 0;i<newRow;i++)
        tmp[i] = new T[newCol];
    for(int i = 0;i<r;i++)
    {
        copy(a[i],a[i]+c,tmp[i]);
    }
    for(int i = 0;i<oldRow;i++)
        delete [] a[i];
    delete [] a;
    a = tmp;
}


int main()
{

    ArrayList<int> ia(5);
    ia.insert(0,1);ia.insert(0,2);ia.insert(0,3);ia.set(3,0);
    std::cout << ia << std::endl;
    for(auto i = ia.begin();i!=ia.end();++i)
        std::cout << *i << " ";
    ArrayList<int> ib(ia);
    cout << (ia!=ib) << endl;

    /*
    //test resizelength2d
    int** a;
    a = new int* [3];
    for(int i =0;i<3;i++)
        a[i] = new int[3];
    resizeLength2D(a,3,3,4,4);
     */
    return 0;
}