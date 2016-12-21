#include <iostream>
#include "chain.h"


int main()
{
    chain<int> ic;
    ic.insert(0,1);ic.insert(0,2);ic.push_back(3);ic.push_back(4);
    chain<int> ic1(ic);ic1.reverse();
    cout << ic1 << endl;
    return 0;
}