// Author: Carter Veit
// Description: Declares prototype for cars structure for use
//              in project 2.
//
// Last Modified: November 2, 2026
// Last Modified By: Carter Veit

#ifndef PROJECT_2_DSA_CARS_H
#define PROJECT_2_DSA_CARS_H

#include <string>

using namespace std;

struct EngineStats{
    int horsepower;
    int torque;
    EngineStats(const int& horsepower_, const int& torque_);
};

struct Dimensions{
    int height;
    int length;
    int width;
    Dimensions(const int& height_, const int& length_, const int& width_);
};

struct EngineInfo{
    string driveline;
    string type;
    bool hybrid;
    int gears;
    string transmission;
    EngineStats stats;
    EngineInfo(const string& driveline_, const string& type_, const bool& hybrid_, const int& gears_,
        const string& transmission_, const EngineStats& stats_);
};

struct FuelInfo{
    int mpg_city;
    string type;
    int mpg_highway;
    FuelInfo(const int& mpg_city_, const string& type_, const int& mpg_highway_);
};

struct Identification{
    string classification;
    string id;
    string make;
    string model_year;
    int year;
    Identification(const string& classification_, const string& id_, const string& make_,
        const string& model_year_, const int& year_);
};

struct Car{
    Dimensions dimen;
    EngineInfo engine;
    FuelInfo fuel;
    Identification iden;
    Car(const Dimensions& dimen_, const EngineInfo& engine_, const FuelInfo& fuel_,
        const Identification& iden_);
    bool operator==(const Car& other);
};

#endif //PROJECT_2_DSA_CARS_H