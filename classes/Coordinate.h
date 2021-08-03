#pragma once

struct Coordinate{
    double longitude; //X
    double latitude; //Y

    Coordinate(double lon, double lat):longitude(lon),latitude(lat){}
    Coordinate(){}

    bool operator<(const Coordinate &coords){
        return this->longitude < coords.longitude && this->latitude < coords.latitude;
    }

    bool operator==(const Coordinate &coords){
        return this->longitude == coords.longitude && this->latitude == coords.latitude;
    }

    bool operator!=(const Coordinate &coords){
        return this->longitude != coords.longitude && this->latitude != coords.latitude;
    }
};