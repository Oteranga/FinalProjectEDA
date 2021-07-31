#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "Taxitrip.h"
#include "Node.h"
#include "Neighborhood.h"
#include "Rectangle.h"

class Rtree{
    private:
        int M;
        int m;
        Node* root;
        Rectangle MBR(vector<Neighborhood> neighs);
        vector<TaxiTrip> get_trips();
        bool same_neighborhood(TaxiTrip taxi_trip);
        void top5_neighborhoods(Node* current, vector<Neighborhood> &result);
        bool trips_begin();
        void overflow_leaf(Node* temp);

        void insert_rec(Node* temp, Neighborhood neighborhood);
        Node* search_rec(Node* temp, Rectangle rect);
        void print_rec(Node* temp);

    public:
        Rtree(int range);
        void insert(Neighborhood element);
        Node* search(Coordinate coord);

        vector<TaxiTrip> query1();
        vector<Neighborhood> query2();
        int query3(Coordinate P1, Coordinate P2);
        vector<TaxiTrip> query4(Coordinate P, double D);
        void print();

};

//PRIVATE

void Rtree::print_rec(Node* temp){
    if(temp->is_leaf()){
        for(auto it: temp->data){
            it.print_neighborhood();
        }
    } else{ 
        for(auto it = temp->elements.begin(); it != temp->elements.end(); it++){
            it->first.print_rectangle();
            print_rec(it->second);
        }
    }
}


vector<TaxiTrip> Rtree::get_trips(){

}


bool Rtree::same_neighborhood(TaxiTrip taxi_trip){

}


void Rtree::top5_neighborhoods(Node* current, vector<Neighborhood> &result){
    
}


Node* Rtree::search_rec(Node* temp, Rectangle rect){
    Node* target;
    /* if(temp->node_bounds.inside_bounds(rect)){
        if(!temp->is_leaf()){
            for(int i=0; i<temp->children.size(); i++){
                return search_rec(temp->children[i],rect);
            }
        } else return temp;
    } */
}


void Rtree::insert_rec(Node* temp, Neighborhood neighborhood){
    if(temp->is_leaf()){
        temp->add_element(neighborhood);
        if(temp->data.size()>M){
            overflow_leaf(temp);
        }
    } else{
        map<Rectangle,Node*> elems = temp->elements;
        bool closest_rect = false;
        pair<Node*,double> target{elems.begin()->second,elems.begin()->first.get_dist(neighborhood.get_bounds())};
        for(auto it = elems.begin(); it != elems.end(); it++){
            if(it->first.inside_bounds(neighborhood.get_bounds())){
                insert_rec(it->second, neighborhood);
                closest_rect = false;
                break;
            } else {
                double temp = it->first.get_dist(neighborhood.get_bounds());
                if(temp<target.second){
                    target.first = it->second;
                    target.second = temp;
                }
                closest_rect = true;
            }
        }
        if(closest_rect)
            insert_rec(target.first,neighborhood);
    }
}


void Rtree::overflow_leaf(Node* temp){
    Rectangle R1 = temp->data[0].get_bounds();
    Rectangle R2 = temp->data[M].get_bounds();
    Node* node1 = new Node();
    Node* node2 = new Node();

    node1->add_element(temp->data[0]);
    node2->add_element(temp->data[M]);

    for(int i = 1; i<M; i++){
        if(R1.get_dist(temp->data[i].get_bounds())<R2.get_dist(temp->data[i].get_bounds()))
            node1->add_element(temp->data[i]);
        else node2->add_element(temp->data[i]);
    }
    
    Rectangle MBR1 = MBR(node1->data);
    Rectangle MBR2 = MBR(node2->data);
    map<Rectangle,Node*> new_elements;
    new_elements.insert({MBR1,node1});
    new_elements.insert({MBR2,node2});
    temp->elements = new_elements;
    temp->data.clear();
}


Rectangle Rtree::MBR(vector<Neighborhood> neighs){
    Coordinate min(neighs[0].get_bounds().get_min("lon"),neighs[0].get_bounds().get_min("lat"));
    Coordinate max(neighs[0].get_bounds().get_max("lon"),neighs[0].get_bounds().get_max("lat"));
    for(int i = 1; i<neighs.size(); i++){
        if(neighs[i].get_bounds().get_min("lon")<min.longitude)
            min.longitude = neighs[i].get_bounds().get_min("lon");
        if(neighs[i].get_bounds().get_min("lat")<min.latitude)
            min.latitude = neighs[i].get_bounds().get_min("lat");
        if(neighs[i].get_bounds().get_max("lon")>max.longitude)
            max.longitude = neighs[i].get_bounds().get_max("lon");
        if(neighs[i].get_bounds().get_max("lat")>max.latitude)
            max.latitude = neighs[i].get_bounds().get_max("lat");
    }
    return Rectangle(min,max);
}


//PUBLIC

Rtree::Rtree(int range){
    root = new Node();
    M = range;
    m = ceil(M/2);
}

void Rtree::print(){
    print_rec(this->root);
}


void Rtree::insert(Neighborhood neighborhood){
    auto temp = this->root;
    insert_rec(temp,neighborhood);
}


Node* Rtree::search(Coordinate coord){
    auto temp = this->root;
    
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