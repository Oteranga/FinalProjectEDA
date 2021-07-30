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

    void add_element(Neighborhood neighborhood){
        data.push_back(neighborhood);
        sort(data.begin(), data.end(),&sort_neighs);
    }
};


bool sort_neighs(const Neighborhood &N1, const Neighborhood &N2){
    Rectangle R1 = N1.get_bounds();
    Rectangle R2 = N2.get_bounds();
    double r1_dist = R1.get_dist(Rectangle({0,0},{0,0}));
    double r2_dist = R2.get_dist(Rectangle({0,0},{0,0}));
    return r1_dist < r2_dist;
}
