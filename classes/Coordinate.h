#pragma once

struct Coordinate{
    double longitude; //X
    double latitude; //Y

    Coordinate(double lon, double lat):longitude(lon),latitude(lat){}
    Coordinate(){}
};