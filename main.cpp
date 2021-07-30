#include <iostream>
#include "classes/Rtree.h"

using namespace std;

int main(){
    Rtree rtree(2);
    rtree.insert(Neighborhood(Rectangle({3,4},{4,5}))); //LM
    rtree.insert(Neighborhood(Rectangle({12,1},{13,2}))); //LLLLM
    rtree.insert(Neighborhood(Rectangle({6,2},{7,3}))); //
    rtree.insert(Neighborhood(Rectangle({8,2},{6,4})));
    return 0;
}