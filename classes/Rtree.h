#pragma once
#include "Taxitrip.h"
#include "Neighborhood.h"
#include <math.h>

class Rtree{
    private:
    int max_range;
    Node* root;
    Rectangle MBR(Rectangle R1, Rectangle R2);
    vector<TaxiTrip> get_trips();
    bool same_neighborhood(TaxiTrip taxi_trip);
    void top5_neighborhoods(Node* current, vector<Neighborhood> &result);
    bool trips_begin();
    bool inside_bounds(Node* temp, Node* new_temp);
    bool cmp_dist_from_origin(Rectangle temp_rect, Rectangle new_rect);
    double get_dist(Rectangle rect1, Rectangle rect2);

    void insert_rec(Node* temp, Node* new_node);

    public:
    Rtree(int range);
    void insert(Neighborhood element);
    Node* search(Coordinate coordinate);
    vector<TaxiTrip> query1();
    vector<Neighborhood> query2();
    int query3(Coordinate P1, Coordinate P2);
    vector<TaxiTrip> query4(Coordinate P, double D);

};

//PRIVATE

bool Rtree::inside_bounds(Node* temp, Node* new_temp){
    Rectangle temp_rect = temp->node_bounds;
    Rectangle new_rect = new_temp->node_bounds;
    if(new_rect.get_min("lon") > temp_rect.get_min("lon") &&
        new_rect.get_min("lat") > temp_rect.get_min("lat") &&
        new_rect.get_max("lon") < temp_rect.get_max("lon") &&
        new_rect.get_max("lat") > temp_rect.get_max("lat"))
        return true;
    else return false;
}


Rectangle Rtree::MBR(Rectangle R1, Rectangle R2){
    Rectangle new_rect;
    if(R1.get_min("lat") < R2.get_min("lat")) 
        new_rect.set_min(R1.get_min("lat"),"lat");
    else 
        new_rect.set_min(R2.get_min("lat"),"lat");

    if(R1.get_min("lon") < R2.get_min("lon")) 
        new_rect.set_min(R1.get_min("lon"),"lon");
    else 
        new_rect.set_min(R2.get_min("lon"),"lon");

    if(R1.get_max("lat") < R2.get_max("lat")) 
        new_rect.set_max(R2.get_max("lat"),"lat");
    else 
        new_rect.set_max(R1.get_max("lat"),"lat");

    if(R1.get_max("lon") < R2.get_max("lon")) 
        new_rect.set_max(R2.get_max("lon"),"lon");
    else 
        new_rect.set_max(R1.get_max("lon"),"lon");

    return new_rect;
}


vector<TaxiTrip> Rtree::get_trips(){

}


bool Rtree::same_neighborhood(TaxiTrip taxi_trip){

}


bool Rtree::cmp_dist_from_origin(Rectangle temp_rect, Rectangle new_rect){
    double temp_dist = get_dist(temp_rect,Rectangle({0,0},{0,0}));
    double new_dist = get_dist(new_rect,Rectangle({0,0},{0,0}));

    if(new_dist>temp_dist)
        return false;
    else return true;
}

double Rtree::get_dist(Rectangle rect1, Rectangle rect2){
    double rect1_lon = (rect1.get_max("lon") - rect1.get_min("lon"))/2;
    double rect1_lat = (rect1.get_max("lat") - rect1.get_min("lat"))/2;

    double rect2_lon = (rect2.get_max("lon") - rect2.get_min("lon"))/2;
    double rect2_lat = (rect2.get_max("lat") - rect2.get_min("lat"))/2;

    return sqrt(pow((rect2_lon-rect1_lon),2)+pow((rect2_lat-rect1_lat),2));
}



void Rtree::insert_rec(Node* temp, Node* new_node){
    vector<Node*> temp_children = temp->children;
    if(temp_children.size() <= max_range){
        if(inside_bounds(temp,new_node)){
            for(int i=0; i<temp_children.size(); i++){
                Rectangle rect1 = temp_children[i]->node_bounds;
                Rectangle rect2 = new_node->node_bounds;
                if(cmp_dist_from_origin(rect1,rect2))
                    temp_children.push_back(new_node);
                else{
                    auto aux = temp_children[i];
                    temp_children[i] = new_node;
                    temp_children.push_back(aux);
                }
            }
        }
    } else {
        Rectangle rect;
        Rectangle rect_begin = temp_children[0]->node_bounds;
        Rectangle rect_end = temp_children[max_range-1]->node_bounds;
        /* for(int i=1; i<max_range-1; i++){
            Rectangle rect_temp = temp_children[i]->node_bounds;
            if(get_dist(rect_begin,rect_temp)>get_dist(rect_end,rect_temp))
                //insertar en el nodo de la izquierda
            else
                //insertar en el nodo de la derecha
        } */
    }
}


//PUBLIC

Rtree::Rtree(int range){
    root = nullptr;
    max_range = range;
}


void Rtree::insert(Neighborhood element){
    auto new_node = new Node(element,element.get_bounds(),true,max_range);
    if(!this->root){
        this->root = new_node;
    }
    else{
        auto temp = this->root;
        insert_rec(temp,new_node);
    }
}


Node* Rtree::search(Coordinate coordinate){
    
}


vector<TaxiTrip> Rtree::query1(){
    vector<TaxiTrip> result;
    vector<TaxiTrip> trips = get_trips();
    for(int i = 0; i < trips.size(); i++){
        if(same_neighborhood(trips[i])) result.push_back(trips[i]);
    }
    return result;
}


vector<Neighborhood> Rtree::query2(){
    vector<Neighborhood> result;
    top5_neighborhoods(root, result);
    // Metodo de ordenacion para obtener los 5 primeros
    return result;
}


int Rtree::query3(Coordinate P1, Coordinate P2){
    int result;
    vector<TaxiTrip> trips = get_trips();
    Rectangle rectangle{P1, P2};
    for(int i = 0; i < trips.size(); i++){
        // Llamada a funcion auxiliar
    }
    return result;
}


vector<TaxiTrip> Rtree::query4(Coordinate P, double D){
    vector<TaxiTrip> result;

    return result;
}