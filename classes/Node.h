#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Coordinate{
    double longitude; //X
    double latitude; //Y

    Coordinate(double lon, double lat):longitude(lon),latitude(lat){}
};

class Rectangle{
    private:
        Coordinate min_bound;
        Coordinate max_bound;

    public:
        void set_min(double num, string coord_type){
            if(coord_type == "lon")
                min_bound.longitude = num;
            else if(coord_type == "lat")
                min_bound.latitude = num;
        }

        void set_max(double num, string coord_type){
            if(coord_type == "lon")
                max_bound.longitude = num;
            else if(coord_type == "lat")
                max_bound.latitude = num;
        }

        double get_min(string coord_type){
            if(coord_type == "lon")
                return min_bound.longitude;
            else if(coord_type == "lat")
                return min_bound.latitude;
        }

        double get_max(string coord_type){
            if(coord_type == "lon")
                return max_bound.longitude;
            else if(coord_type == "lat")
                return max_bound.latitude;
        }

        Rectangle(Coordinate min, Coordinate max): min_bound(min), max_bound(max){}
        Rectangle();
};

struct Node{
    Neighborhood element;
    Rectangle node_bounds;
    vector<Node*> children;
    bool is_leaf;
    Node(Neighborhood elem, Rectangle bounds, bool position, int size){ 
        element = elem;
        node_bounds = bounds; 
        is_leaf = position;
    }

};