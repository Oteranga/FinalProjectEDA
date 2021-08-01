#pragma once
#include <vector>
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

        Rectangle get_bounds()const{
            return bounds;
        }

        void print_neighborhood(){
            cout << "Neighborhood: \n";
            bounds.print_rectangle();
        }

        bool operator!=(const Neighborhood &neighborhood)const{
            return bounds != neighborhood.bounds;
        }

        bool operator==(const Neighborhood &neighborhood)const{
            return bounds == neighborhood.bounds;
        }
};