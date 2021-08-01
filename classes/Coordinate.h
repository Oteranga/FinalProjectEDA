#pragma once

struct Coordinate{
    double longitude; //X
    double latitude; //Y

    Coordinate(double lon, double lat):longitude(lon),latitude(lat){}
    Coordinate(){}

    bool operator<(const Coordinate &coords)const{
        return longitude < coords.longitude && latitude < coords.latitude;
    }

    bool operator==(const Coordinate &coords)const{
        return longitude == coords.longitude && latitude == coords.latitude;
    }

    bool operator!=(const Coordinate &coords)const{
        return longitude != coords.longitude && latitude != coords.latitude;
    }
};