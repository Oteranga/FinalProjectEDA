#pragma once
#include "Node.h"

struct Neighborhood{
    string name;
    string borough;
    string geometry_type;
    vector<Coordinate> coordinates;
    int number_of_trips;
    Rectangle limits;
};