#pragma once
#include "Node.h"
#include "TaxiTrip.h"
#include "Neighborhood.h"

template <typename T>
class Rtree{
    private:
    Node<T>* root;
    Rectangle MBR(Rectangle R1, Rectangle R2);
    vector<TaxiTrip> get_trips();
    bool same_neighborhood(TaxiTrip taxi_trip);
    void top5_neighborhoods(Node<T>* current, vector<Neighborhood> &result);
    bool trips_begin();
    public:
    Rtree():root(nullptr){}

    void insert(T element, Coordinate coordinate);
    Node<T>* search(Coordinate coordinate);
    vector<TaxiTrip> query1();
    vector<Neighborhood> query2();
    int query3(Coordinate P1, Coordinate P2);
    vector<TaxiTrip> query4(Coordinate P, double D);

};

//PRIVATE

template<typename T>
Rectangle Rtree<T>::MBR(Rectangle R1, Rectangle R2){
    Coordinate min_coordinate;
    Coordinate max_coordinate;
    if(R1.min_xy.latitude < R2.min_xy.latitude) min_coordinate.latitude = R1.min_xy.latitude;
    else min_coordinate.latitude = R2.min_xy.latitude;
    if(R1.min_xy.longitude < R2.min_xy.longitude) min_coordinate.longitude = R1.min_xy.longitude;
    else min_coordinate.longitude = R2.min_xy.longitude;

    if(R1.max_xy.latitude < R2.max_xy.latitude) max_coordinate.latitude = R2.max_xy.latitude;
    else max_coordinate.latitude = R1.max_xy.latitude;
    if(R1.max_xy.longitude < R2.max_xy.longitude) max_coordinate.longitude = R2.max_xy.longitude;
    else max_coordinate.longitude = R1.max_xy.longitude;

    Rectangle new_rectangle(min_coordinate, max_coordinate);
    return new_rectangle;
}

template<typename T>
vector<TaxiTrip> Rtree<T>::get_trips(){

}

template<typename T>
bool Rtree<T>::same_neighborhood(TaxiTrip taxi_trip){

}

//PUBLIC

template<typename T, typename type>
void Rtree<T>::insert(T element, type location){

}

template<typename T>
vector<TaxiTrip> Rtree<T>::query1(){
    vector<TaxiTrip> result;
    vector<TaxiTrip> trips = get_trips();
    for(int i = 0; i < trips.size(); i++){
        if(same_neighborhood(trips[i])) result.push_back(trips[i]);
    }
    return result;
}

template<typename T>
vector<Neighborhood> Rtree<T>::query2(){
    vector<Neighborhood> result;
    top5_neighborhoods(root, result);
    // Metodo de ordenacion para obtener los 5 primeros
    return result;
}

template<typename T>
int Rtree<T>::query3(Coordinate P1, Coordinate P2){
    int result;
    vector<TaxiTrip> trips = get_trips();
    Rectangle rectangle(P1, P2);
    for(int i = 0; i < trips.size(); i++){
        // Llamada a funcion auxiliar
    }
    return result;
}

template<typename T>
vector<TaxiTrip> Rtree<T>::query4(Coordinate P, double D){
    vector<TaxiTrip> result;

    return result;
}