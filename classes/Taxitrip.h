#pragma once
#include "Node.h"

struct TaxiTrip{
    int trip_id;
    float trip_distance;
    Coordinate pickup;
    Coordinate dropoff;
};