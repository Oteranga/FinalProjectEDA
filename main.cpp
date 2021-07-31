#include <iostream>
#include "classes/Rtree.h"

using namespace std;

int main(){
    Rtree rtree(3);
    rtree.insert(Neighborhood(Rectangle({3,4},{4,5}))); //LM
    rtree.insert(Neighborhood(Rectangle({12,1},{13,2}))); //LLLLM
    rtree.insert(Neighborhood(Rectangle({6,2},{7,3}))); //LL1
    rtree.insert(Neighborhood(Rectangle({8,2},{9,3}))); //LLL1
    rtree.print();
    return 0;
}