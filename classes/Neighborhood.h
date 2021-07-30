#pragma once
#include <vector>
#include "Rectangle.h"

class Neighborhood{
    private:
        string name;
        string borough;
        string geometry_type;
        vector<Coordinate> coordinates;
        int number_of_trips;
        Rectangle bounds;

    public:
        Neighborhood(Rectangle rect):bounds(rect){}

        Neighborhood(){}

        bool is_inside(Coordinate coord){
            return false;
        }

        Rectangle get_bounds(){
            return bounds;
        }
};