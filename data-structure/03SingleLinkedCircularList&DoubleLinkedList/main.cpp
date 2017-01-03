#include <iostream>
#include "DoubleLinkedList.h"
#include "SingleLinkedCircularList.h"


int main()
{
    SingleLinkedCircularList<int> sa;
    sa.insert(0,1);sa.push_back(2);sa.push_back(3);
    sa.output(cout);
    std::cout << *sa.begin() << std::endl;
    return 0;
}