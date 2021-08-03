#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <tuple>

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
        pair<Neighborhood,Neighborhood> farthest_pair_leaf(vector<Neighborhood> neighborhoods);
        void set_position(vector<Neighborhood> neighborhoods, Node* node1, Node* node2);
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
            cout << "================ \n";
            cout << "MBR: \n";
            Rectangle rect_temp = it->first;
            rect_temp.print_rectangle();
            cout << "================ \n";
            print_rec(it->second);
        }
    }
}


vector<TaxiTrip> Rtree::get_trips(){
    vector<TaxiTrip> output;
    return output;

}


bool Rtree::same_neighborhood(TaxiTrip taxi_trip){
    return false;
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
    return target;
}


void Rtree::insert_rec(Node* temp, Neighborhood neighborhood){
    if(temp->is_leaf()){
        temp->data.push_back(neighborhood);
        if(temp->data.size()>M){
            overflow_leaf(temp);
        }
    } else{
        map<Rectangle,Node*> elems = temp->elements;
        bool closest_rect = false;
        Rectangle rect_base = elems.begin()->first;
        Node* node_base = elems.begin()->second;
        double dist_base = rect_base.get_dist(neighborhood.get_bounds());

        for(auto it = elems.begin(); it != elems.end(); it++){
            Rectangle it_rect = it->first;
            if(it_rect.inside_bounds(neighborhood.get_bounds())){
                insert_rec(it->second, neighborhood);
                closest_rect = false;
                break;
            } else {
                double temp_dist = it_rect.get_dist(neighborhood.get_bounds());
                if(temp_dist < dist_base){
                    rect_base = it->first;
                    node_base = it->second;
                    dist_base = temp_dist;
                }
                closest_rect = true;
            }
        }

        if(closest_rect){
            Rectangle rect = rect_base.MBR(neighborhood.get_bounds());
            pair<Rectangle,Node*> new_elem{rect,node_base};
            temp->elements.erase(rect_base);
            temp->elements.insert(new_elem);
            insert_rec(node_base,neighborhood);
        }
    }
}

pair<Neighborhood,Neighborhood> Rtree::farthest_pair_leaf(vector<Neighborhood> neighborhoods){
    pair<Neighborhood,Neighborhood> farthest;
    double max_area = 0;
    for(int i=0; i<neighborhoods.size(); i++){
        for(int j=i+1; j<neighborhoods.size()+1; j++){
            Rectangle rect1 = neighborhoods[i].get_bounds();
            Rectangle rect2 = neighborhoods[j].get_bounds();
            Rectangle temp_rect = rect1.MBR(rect2);
            double area = temp_rect.area() - rect1.area() - rect2.area();
            if(area > max_area){
                max_area = area;
                farthest.first = neighborhoods[i];
                farthest.second = neighborhoods[j];
            }
        }
    }
    return farthest;
}


void Rtree::set_position(vector<Neighborhood> neighborhoods, Node* node1, Node* node2){
    Rectangle R1 = node1->data[0].get_bounds();
    Rectangle R2 = node2->data[0].get_bounds();
    int i=0;
    while(node1->data.size()<(M-m+1) && node2->data.size()<(M-m+1) && i<neighborhoods.size()){
        if(neighborhoods[i] != node1->data[0] && neighborhoods[i] != node2->data[0]){
            Neighborhood neigh = neighborhoods[i];
            double a1 = R1.area_to_increase(neigh.get_bounds());
            double a2 = R2.area_to_increase(neigh.get_bounds());
            if(a1 < a2) node1->data.push_back(neigh);
            else if(a2 < a1) node2->data.push_back(neigh);
        }
        i++;
    }
    if(i<neighborhoods.size()-1){
        if(node1->data.size()==(M-m+1)){ 
            for(int j=i; j<neighborhoods.size(); j++){
                node2->data.push_back(neighborhoods[j]);
            }
        } else if(node2->data.size()==(M-m+1)){
            for(int j=i; j<neighborhoods.size(); j++){
                node1->data.push_back(neighborhoods[j]);
            }
        }
    }
}


void Rtree::overflow_leaf(Node* temp){
    Node* node1 = new Node();
    Node* node2 = new Node();
    vector<Neighborhood> temp_data = temp->data;
    pair<Neighborhood,Neighborhood> farthest = farthest_pair_leaf(temp_data);
    node1->data.push_back(farthest.first);
    node2->data.push_back(farthest.second);
    
    set_position(temp->data,node1,node2);
    
    Rectangle MBR1 = MBR(node1->data);
    Rectangle MBR2 = MBR(node2->data);
    temp->elements.insert({MBR1,node1});
    temp->elements.insert({MBR2,node2});
    /* temp->elements[MBR1] = node1;
    temp->elements[MBR2] = node2; */
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
    return temp;
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