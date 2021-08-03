#include <iostream>
#include "classes/Rtree.h"

using namespace std;

int main(){
    Rtree rtree(3);
    rtree.insert(Neighborhood(Rectangle({3,4},{4,5}))); 
    rtree.insert(Neighborhood(Rectangle({12,1},{13,2})));
    rtree.insert(Neighborhood(Rectangle({6,2},{7,3})));
    rtree.insert(Neighborhood(Rectangle({8,2},{9,3}))); 
    rtree.insert(Neighborhood(Rectangle({8,4},{9,5}))); 
    //rtree.insert(Neighborhood(Rectangle({11,7},{12,8}))); 
    //rtree.insert(Neighborhood(Rectangle({11,3},{12,4}))); 
    //rtree.insert(Neighborhood(Rectangle({14,6},{15,7}))); 

    rtree.print();
    return 0;
}