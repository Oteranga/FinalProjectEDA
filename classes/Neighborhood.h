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
        Rectangle bounds;

    public:
        int number_of_trips;
        Neighborhood(Rectangle rect):bounds(rect){}

        Neighborhood(){}

        bool is_inside(Coordinate coord){
            bool result = false;
            for (int i = 0, j = coordinates.size()-1; i < coordinates.size(); j = i++) {
                if(coord == coordinates[i])
                    return true;
                if ((((coordinates[i].latitude<=coord.latitude) && (coord.latitude<coordinates[j].latitude)) 
                || ((coordinates[j].latitude<=coord.latitude) && (coord.latitude<coordinates[i].latitude))) &&
                (coord.longitude < (coordinates[j].longitude - coordinates[i].longitude) * (coord.latitude - coordinates[i].latitude) / (coordinates[j].latitude - coordinates[i].latitude) + coordinates[i].longitude))
                    result = !result; 
            } 
            return result; 
        }

        Rectangle get_bounds(){
            return bounds;
        }

        void print_neighborhood(){
            cout << "Neighborhood: \n";
            bounds.print_rectangle();
        }

        bool operator!=(const Neighborhood &neighborhood) const{
            return this->bounds != neighborhood.bounds;
        }

        bool operator==(const Neighborhood &neighborhood) const{
            return this->bounds == neighborhood.bounds;
        }
};