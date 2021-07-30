#pragma once
#include "Coordinate.h"

using namespace std;

struct TaxiTrip{
    int trip_id;
    float trip_distance;
    Coordinate pickup;
    Coordinate dropoff;

    void get_data(){
        cout << trip_id << "\n";
        cout << trip_distance << "\n";
        cout << pickup.latitude << "\n";
        cout << pickup.longitude << "\n";
        cout << dropoff.latitude << "\n";
        cout << dropoff.longitude << "\n";
    }
};