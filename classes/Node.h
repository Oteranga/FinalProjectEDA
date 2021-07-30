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
        elements.insert(pair<Rectangle,Node*>(Rectangle({0,0},{0,0}),nullptr));
    }

    bool is_leaf(){ return elements.size()==1; }
};

struct sort_neighs{
    bool operator()(const Rectangle &R1, const Rectangle &R2){
        double r1_dist = R1.get_dist(Rectangle({0,0},{0,0}));
        double r2_dist = R2.get_dist(Rectangle({0,0},{0,0}));
        return r1_dist < r2_dist;
    }
};
