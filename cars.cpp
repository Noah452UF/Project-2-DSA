// Author: Carter Veit
// Description: Defines functions for cars structure for use
//              in project 2.
//
// Last Modified: November 2, 2026
// Last Modified By: Carter Veit

#include "cars.h"

EngineStats::EngineStats(const int &horsepower_, const int &torque_) {
    horsepower = horsepower_;
    torque = torque_;
}

Dimensions::Dimensions(const int &height_, const int &length_, const int &width_) {
    height = height_;
    length = length_;
    width = width_;
}

EngineInfo::EngineInfo(const string &driveline_, const string &type_, const bool &hybrid_,
    const int &gears_, const string &transmission_, const EngineStats &stats_) : stats(stats_) {
    driveline = driveline_;
    type = type_;
    hybrid = hybrid_;
    gears = gears_;
    transmission = transmission_;
}

FuelInfo::FuelInfo(const int &mpg_city_, const string &type_, const int &mpg_highway_) {
    mpg_city = mpg_city_;
    type = type_;
    mpg_highway = mpg_highway_;
}

Identification::Identification(const string &classification_, const string &id_, const string &make_,
    const string &model_year_, const int &year_) {
    classification = classification_;
    id = id_;
    make = make_;
    model_year = model_year_;
    year = year_;
}

Car::Car(const Dimensions &dimen_, const EngineInfo &engine_, const FuelInfo &fuel_,
    const Identification &iden_) : dimen(dimen_), engine(engine_), fuel(fuel_), iden(iden_) {}

bool Car::operator==(const Car &other) {
    if (iden.id == other.iden.id) {
        return true;
    }

    return false;
}
