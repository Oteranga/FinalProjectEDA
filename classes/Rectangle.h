#pragma once
#include <string>
#include "Coordinate.h"

using namespace std;

class Rectangle{
    private:
        Coordinate min_bound;
        Coordinate max_bound;

    public:
        Rectangle(Coordinate min, Coordinate max): min_bound(min), max_bound(max){}
        Rectangle(){}
        void set_min(double num, string coord_type);
        void set_max(double num, string coord_type);
        double get_min(string coord_type)const;
        double get_max(string coord_type)const;
        bool inside_bounds(Rectangle new_rect);
        double get_dist(Rectangle rect)const;
        Rectangle MBR(Rectangle rect);

        bool operator==(const Rectangle &rect) const{
            double this_dist = get_dist(Rectangle({0,0},{0,0}));
            double rect_dist = rect.get_dist(Rectangle({0,0},{0,0}));
            return this_dist == rect_dist;
        }

        bool operator<(const Rectangle &rect) const{
            double this_dist = get_dist(Rectangle({0,0},{0,0}));
            double rect_dist = rect.get_dist(Rectangle({0,0},{0,0}));
            return this_dist < rect_dist;
        }
};


void Rectangle::set_min(double num, string coord_type){
    if(coord_type == "lon")
        min_bound.longitude = num;
    else if(coord_type == "lat")
        min_bound.latitude = num;
}

void Rectangle::set_max(double num, string coord_type){
    if(coord_type == "lon")
        max_bound.longitude = num;
    else if(coord_type == "lat")
        max_bound.latitude = num;
}

double Rectangle::get_min(string coord_type)const{
    if(coord_type == "lon")
        return min_bound.longitude;
    else if(coord_type == "lat")
        return min_bound.latitude;
    return -1;
}

double Rectangle::get_max(string coord_type)const{
    if(coord_type == "lon")
        return max_bound.longitude;
    else if(coord_type == "lat")
        return max_bound.latitude;
    return -1;
}

bool Rectangle::inside_bounds(Rectangle new_rect){
    if(new_rect.get_min("lon") > this->get_min("lon") &&
        new_rect.get_min("lat") > this->get_min("lat") &&
        new_rect.get_max("lon") < this->get_max("lon") &&
        new_rect.get_max("lat") < this->get_max("lat"))
        return true;
    return false;
}

double Rectangle::get_dist(Rectangle rect)const{
    double this_lon = ((this->get_max("lon") - this->get_min("lon"))/2) + this->get_min("lon");
    double this_lat = ((this->get_max("lat") - this->get_min("lat"))/2) + this->get_min("lat");

    double rect_lon = ((rect.get_max("lon") - rect.get_min("lon"))/2) + rect.get_min("lon");
    double rect_lat = ((rect.get_max("lat") - rect.get_min("lat"))/2) + rect.get_min("lat");

    return sqrt(pow((rect_lon-this_lon),2)+pow((rect_lat-this_lat),2));
}

Rectangle Rectangle::MBR(Rectangle rect){
    Rectangle new_rect;
    if(this->get_min("lat") < rect.get_min("lat")) 
        new_rect.set_min(this->get_min("lat"),"lat");
    else 
        new_rect.set_min(rect.get_min("lat"),"lat");

    if(this->get_min("lon") < rect.get_min("lon")) 
        new_rect.set_min(this->get_min("lon"),"lon");
    else 
        new_rect.set_min(rect.get_min("lon"),"lon");

    if(this->get_max("lat") < rect.get_max("lat")) 
        new_rect.set_max(rect.get_max("lat"),"lat");
    else 
        new_rect.set_max(this->get_max("lat"),"lat");

    if(this->get_max("lon") < rect.get_max("lon")) 
        new_rect.set_max(rect.get_max("lon"),"lon");
    else 
        new_rect.set_max(this->get_max("lon"),"lon");

    return new_rect;
}
