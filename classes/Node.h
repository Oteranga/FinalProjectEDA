#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Rectangle.h"
#include "Neighborhood.h"

using namespace std;

struct Node{
    vector<Neighborhood> data;
    map<Rectangle,Node*> elements;

    Node(){
        //elements.insert(pair<Rectangle,Node*>(Rectangle({0,0},{0,0}),nullptr));
    }

    bool is_leaf(){ return elements.empty(); }


};