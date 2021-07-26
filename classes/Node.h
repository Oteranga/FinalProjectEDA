#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct Coordinate{
    double latitude; //Y
    double longitude; //X
};

struct Rectangle{
    Coordinate min_xy;
    Coordinate max_xy;
    Rectangle(Coordinate min, Coordinate max): min_xy(min), max_xy(max){}
};

template<typename T>
struct Node{
    T element;
    vector<Node*> children;
};