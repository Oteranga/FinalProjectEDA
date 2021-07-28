#pragma once
#include "Node.h"

class Neighborhood{
    private:
        string name;
        string borough;
        string geometry_type;
        vector<Coordinate> coordinates;
        int number_of_trips;
        Rectangle bounds;

    public:
        bool is_inside(Coordinate coord){
            return false;
        }

        Rectangle get_bounds(){
            return bounds;
        }
};