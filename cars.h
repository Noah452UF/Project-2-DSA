// Author: Carter Veit
// Description: Declares prototype for cars structure for use
//              in project 2.
//
// Last Modified: November 2, 2026
// Last Modified By: Carter Veit

#ifndef PROJECT_2_DSA_CARS_H
#define PROJECT_2_DSA_CARS_H

#include <string>;

struct EngineStats{
    int horsepower;
    int torque;
    EngineSats(int horsepower_, int torque_);
};

struct Dimensions{
    int height;
    int length;
    int width;
    Dimensions(int height_, int length_, int width_);
};

struct EngineInfo{
    string driveline;
    string type;
    bool hybrid;
    int gears;
    string transmission;
    EngineStats stats;
    EngineInfo(string driveline_, string type_, bool hybrid_, int gears_, string transmission_, EngineStats stats_);
};

struct FuelInfo{
    int mpg_city;
    string type;
    int mpg_highway;
    FuelInfo(int mpg_city_, string type_, int mpg_highway_);
};

struct Identification{
    string classification;
    string id;
    string make;
    string model_year;
    int year;
    Identification(string classification_, string id_, string make_, string model_year_, int year_);
};

struct Car{
    Dimensions dimen;
    EngineInfo engine;
    FuelInfo fuel;
    Identification iden;
    Car(Dimensions dimen_, EngineInfo engine_, FuelInfo fuel_, Identification iden_);
};

#endif //PROJECT_2_DSA_CARS_H