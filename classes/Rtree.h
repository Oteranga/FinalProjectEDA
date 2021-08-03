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
        Rectangle MBR_leaf(vector<Neighborhood> neighs);
        Rectangle MBR_inner(map<Rectangle,Node*> elems);
        vector<TaxiTrip> get_trips();

        //Auxiliar functions for query functions
        bool same_neighborhood(Node* temp, TaxiTrip taxitrip);
        void top5_neighborhoods(Node* temp, Coordinate start_point, vector<Neighborhood> &result);
        bool trips_begin_in(Rectangle rect);

        Node* overflow_leaf(Node* temp);
        Node* overflow_inner(Node* temp);
        pair<Neighborhood,Neighborhood> farthest_pair_leaf(vector<Neighborhood> neighborhoods);
        pair<Rectangle,Rectangle> farthest_pair_inner(map<Rectangle,Node*> elems);
        void set_position_leaf(vector<Neighborhood> neighborhoods, Node* node1, Node* node2);
        void set_position_inner(map<Rectangle,Node*> elems, Node* node1, Node* node2);
        pair<int,Neighborhood> pick_leaf(vector<Neighborhood> neighborhoods, Rectangle R1, Rectangle R2);
        pair<Rectangle,Node*> pick_inner(map<Rectangle,Node*> elems, Rectangle R1, Rectangle R2);
        Node* insert_rec(Node* temp, Neighborhood neighborhood);
        Node* search_rec(Node* temp, Rectangle rect);
        void print_rec(Node* temp);

    public:
        Rtree(int range);
        void insert(Neighborhood element);
        Node* search(Coordinate coord);

        //Query functions
        int query1();
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


bool Rtree::same_neighborhood(Node* temp, TaxiTrip taxitrip){
    Rectangle trip_rect({taxitrip.pickup,taxitrip.dropoff});
    if(temp->is_leaf()){
        for(int i=0; i<temp->data.size(); i++){
            Rectangle rect = temp->data[i].get_bounds();
            if(rect.inside_bounds(trip_rect)){
                if(temp->data[i].is_inside(taxitrip.pickup) && temp->data[i].is_inside(taxitrip.dropoff))
                    return true;
            }
        }
        return false;
    } else {
        for(auto it=temp->elements.begin(); it!=temp->elements.end(); it++){
            Rectangle rect = it->first;
            if(!rect.inside_bounds(trip_rect)) return false;
            else return same_neighborhood(it->second,taxitrip);
        }
    }
    return false;
}


void Rtree::top5_neighborhoods(Node* temp, Coordinates start_point, vector<Neighborhood> &result){
    if(temp->is_leaf()){
        for(int i=0; i<temp->data.size(); i++){
            result.push_back(temp->data[i]);
            Rectangle rect = temp->data[i].get_bounds();
            if(rect.is_inside(start_point)){
                if(temp->data[i].is_inside(taxitrip.pickup) && temp->data[i].is_inside(taxitrip.dropoff))
                    result[i].number_of_trips++;
            }
        }
    } else {
        for(auto it=temp->elements.begin(); it!=temp->elements.end(); it++){
            Rectangle rect = it->first;
            if(!rect.is_inside(start_point)) return;
            else return top5_neighborhoods(it->second, start_point, result);
        }
    }
}

bool Rtree::trips_begin_in(Rectangle rect){
    
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


Node* Rtree::insert_rec(Node* temp, Neighborhood neighborhood){
    if(temp->is_leaf()){
        temp->data.push_back(neighborhood);
        if(temp->data.size()>M){
            *temp = *overflow_leaf(temp);
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
            insert_rec(node_base, neighborhood);
            if(temp->elements.size()>M)
                *temp = *overflow_inner(temp);
        }
    }
}

pair<Rectangle,Rectangle> Rtree::farthest_pair_inner(map<Rectangle,Node*> elems){
    pair<Rectangle,Rectangle> farthest;
    double max_area = 0;
    for(auto it = elems.begin(); it != elems.end(); it++){
        for(auto it2 = next(it); it2 != elems.end(); it2++){
            Rectangle rect1 = it->first;
            Rectangle rect2 = it2->first;
            Rectangle temp_rect = rect1.MBR(rect2);
            double area = temp_rect.area() - rect1.area() - rect2.area();
            if(area > max_area){
                max_area = area;
                farthest.first = rect1;
                farthest.second = rect2;
            }
        }
    }
    return farthest;
}

pair<Neighborhood,Neighborhood> Rtree::farthest_pair_leaf(vector<Neighborhood> neighborhoods){
    pair<Neighborhood,Neighborhood> farthest;
    double max_area = 0;
    for(int i=0; i<neighborhoods.size(); i++){
        for(int j=i+1; j<neighborhoods.size(); j++){
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

void Rtree::set_position_inner(map<Rectangle,Node*> elems, Node* node1, Node* node2){
    Rectangle R1 = node1->elements.begin()->first;
    Rectangle R2 = node2->elements.begin()->first;
    map<Rectangle,Node*> temp_elems = elems;
    while(1){
        if(temp_elems.size()==0 || (node1->elements.size()>=(M-m+1)) || (node2->elements.size()>=(M-m+1))) break;
        pair<Rectangle,Node*> elem = pick_inner(elems,R1,R2);
        if(elem.first != R1 && elem.first != R2){
            double a1 = R1.area_to_increase(elem.first);
            double a2 = R2.area_to_increase(elem.first);
            if(a1 < a2) node1->elements.insert(elem);
            else if(a2 < a1) node2->elements.insert(elem);
            else if(node1->elements.size() < node2->elements.size()) node1->elements.insert(elem);
            else node2->elements.insert(elem);
        }
        temp_elems.erase(elem.first);
    }

    if(node1->elements.size()==(M-m+1)){ 
        for(auto it = elems.begin(); it!=temp_elems.end(); it++){
            node2->elements.insert(*it);
        }
    } else if(node2->elements.size()==(M-m+1)){
        for(auto it = elems.begin(); it!=temp_elems.end(); it++){
            node1->elements.insert(*it);
        }
    }

}

void Rtree::set_position_leaf(vector<Neighborhood> neighborhoods, Node* node1, Node* node2){
    Rectangle R1 = node1->data[0].get_bounds();
    Rectangle R2 = node2->data[0].get_bounds();
    vector<Neighborhood> temp_neighs = neighborhoods;
    while(1){
        if(temp_neighs.size()==0 || (node1->data.size()>=(M-m+1)) || (node2->data.size()>=(M-m+1))) break;
        pair<int,Neighborhood> neigh = pick_leaf(temp_neighs,R1,R2);
        if(!(neigh.second == node1->data[0]) && !(neigh.second == node2->data[0])){
            double a1 = R1.area_to_increase(neigh.second.get_bounds());
            double a2 = R2.area_to_increase(neigh.second.get_bounds());
            if(a1 < a2) node1->data.push_back(neigh.second);
            else if(a2 < a1) node2->data.push_back(neigh.second);
            else if(node1->elements.size() < node2->elements.size()) node1->data.push_back(neigh.second);
            else node2->data.push_back(neigh.second);   
        }
        temp_neighs.erase(temp_neighs.begin()+neigh.first);
    }

    if(node1->data.size()==(M-m+1)){ 
        for(int i=0; i<temp_neighs.size(); i++){
            node2->data.push_back(temp_neighs[i]);
        }
    } else if(node2->data.size()==(M-m+1)){
        for(int i=0; i<temp_neighs.size(); i++){
            node1->data.push_back(temp_neighs[i]);
        }
    }
}

pair<int,Neighborhood> Rtree::pick_leaf(vector<Neighborhood> neighborhoods, Rectangle R1, Rectangle R2){
    double max_area = 0;
    Neighborhood next_to_pick;
    int neigh_pos=0;
    for(int i=0; i<neighborhoods.size(); i++){
        if(!(neighborhoods[i].get_bounds() == R1 && neighborhoods[i].get_bounds() == R2)){
            double area1 = R1.area_to_increase(neighborhoods[i].get_bounds());
            double area2 = R2.area_to_increase(neighborhoods[i].get_bounds());
            double area = abs(area1 - area2);
            if(area > max_area){
                max_area = area;
                next_to_pick = neighborhoods[i];
                neigh_pos = i;
            }
        }
    }
    return {neigh_pos,next_to_pick};
}

pair<Rectangle,Node*> Rtree::pick_inner(map<Rectangle,Node*> elems, Rectangle R1, Rectangle R2){
    double max_area = 0;
    pair<Rectangle,Node*> next_to_pick;
    for(auto it = elems.begin(); it != elems.end(); it++){
        if(!(it->first == R1 && it->first == R2)){
            double area1 = R1.area_to_increase(it->first);
            double area2 = R2.area_to_increase(it->first);
            double area = abs(area1 - area2);
            if(area > max_area){
                max_area = area;
                next_to_pick = *it;
            }
        }
    }
    return next_to_pick;
}


Node* Rtree::overflow_inner(Node* temp){
    Node* node1 = new Node();
    Node* node2 = new Node();
    map<Rectangle,Node*> temp_elems = temp->elements;
    pair<Rectangle,Rectangle> farthest = farthest_pair_inner(temp_elems);
    node1->elements.insert({farthest.first,temp->elements[farthest.first]});
    node2->elements.insert({farthest.second,temp->elements[farthest.second]});
    
    set_position_inner(temp->elements,node1,node2);

    Rectangle MBR1 = MBR_inner(node1->elements);
    Rectangle MBR2 = MBR_inner(node2->elements);

    Node* new_node = new Node();
    new_node->elements.insert({MBR1,node1});
    new_node->elements.insert({MBR2,node2});
    return new_node;
}


Node* Rtree::overflow_leaf(Node* temp){
    Node* node1 = new Node();
    Node* node2 = new Node();
    vector<Neighborhood> temp_data = temp->data;
    pair<Neighborhood,Neighborhood> farthest = farthest_pair_leaf(temp_data);
    node1->data.push_back(farthest.first);
    node2->data.push_back(farthest.second);
    
    set_position_leaf(temp->data,node1,node2);
    
    Rectangle MBR1 = MBR_leaf(node1->data);
    Rectangle MBR2 = MBR_leaf(node2->data);

    Node* new_node = new Node();
    new_node->elements.insert({MBR1,node1});
    new_node->elements.insert({MBR2,node2});
    return new_node;
}

Rectangle Rtree::MBR_inner(map<Rectangle,Node*> elems){
    map<Rectangle,Node*> temp_elems = elems;
    Rectangle rect = temp_elems.begin()->first;
    Coordinate min(rect.get_min("lon"),rect.get_min("lat"));
    Coordinate max(rect.get_max("lon"),rect.get_max("lat"));
    for(auto it = elems.begin(); it != elems.end(); it++){
        auto temp_it = it->first;
        if(temp_it.get_min("lon")<min.longitude)
            min.longitude = temp_it.get_min("lon");
        if(temp_it.get_min("lat")<min.latitude)
            min.latitude = temp_it.get_min("lat");
        if(temp_it.get_max("lon")>max.longitude)
            max.longitude = temp_it.get_max("lon");
        if(temp_it.get_max("lat")>max.latitude)
            max.latitude = temp_it.get_max("lat");
    }
    return Rectangle(min,max);
}

Rectangle Rtree::MBR_leaf(vector<Neighborhood> neighs){
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
    m = ceil(range/2.0);
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


int Rtree::query1(){
    vector<TaxiTrip> result;
    vector<TaxiTrip> trips = get_trips();
    auto temp = this->root;
    for(int i = 0; i < trips.size(); i++){
        if(same_neighborhood(temp,trips[i])) result.push_back(trips[i]);
    }
    return result.size();
}


vector<Neighborhood> Rtree::query2(){
    vector<TaxiTrip> trips = get_trips();
    vector<Neighborhood> result;
    auto temp = this->root;
    for(int i = 0; i < trips.size(); i++){
        top5_neighborhoods(temp, trips[i].pickup, result);
    }
    for(int i = 0; i < result.size(); i++){
        for(int j = 0; j < trips.size(); j++){
            if(result)
        }
    }
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