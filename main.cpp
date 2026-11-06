#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include "cars.h"
#include "heap.cpp"
#include "bplus.cpp"
#include "cars.h"
#include "heap.h"
#include "bplus.h"
#include "json.hpp"
#include <chrono>
using json = nlohmann::json;
using namespace std;


// read cars.json with nlohmann library
vector<Car> readJson(const string& filename) {
    vector<Car> cars;

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("could not open: " + filename);
    }

    json jsonData;
    file >> jsonData;

    for (const auto& item : jsonData) {
        auto dimensions = item["Dimensions"]; // heigh, length, width
        auto engineInfo = item["Engine Information"]; //general engine info
        auto engineStats = engineInfo["Engine Statistics"]; //hp and torque
        auto fuelInfo = item["Fuel Information"]; //mpg etc
        auto identification = item["Identification"]; // make, "model year"

        Dimensions dimensionsObj(dimensions["Height"],
            dimensions["Length"],
            dimensions["Width"]
        );

        EngineStats engineStatsObj(
            engineStats["Horsepower"],
            engineStats["Torque"]
        );

        EngineInfo engineInfoObj(
            engineInfo["Driveline"],
            engineInfo["Engine Type"],
            engineInfo["Hybrid"],
            engineInfo["Number of Forward Gears"],
            engineInfo["Transmission"],
            engineStatsObj

        );

        FuelInfo fuelInfoObj(
            fuelInfo["City mpg"],
            fuelInfo["Fuel Type"],
            fuelInfo["Highway mpg"]
        );

        Identification identificationObj(
            identification["Classification"],
            identification["ID"],
            identification["Make"],
            identification["Model Year"],
            identification["Year"]
        );

        Car car(dimensionsObj, engineInfoObj, fuelInfoObj, identificationObj);
        cars.push_back(car);

    }


    return cars;
}

// read requirements.json and store data in unordered map
unordered_map<string, json> readSortingRequirements(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("could not open: " + filename);
    }

    unordered_map<string, json> sortingReqs;
    json reqsData;
    file >> reqsData;

    for (auto& [key, value] : reqsData.items()) {
        sortingReqs[key] = value;
    }

    return sortingReqs;
}

// writes the top cars to results.json
void writeResults(const vector<Car>& topCars, string& time, const string& filename){

    // add the top cars to resultsJson
    json resultsJson = json::array();
    for (const auto& car : topCars) {
        // json car object
        json carJson;

        // create the json structure for each car
        carJson["Dimensions"]["Height"] = car.dimen.height;
        carJson["Dimensions"]["Length"] = car.dimen.length;
        carJson["Dimensions"]["Width"] = car.dimen.width;

        carJson["Engine Information"]["Driveline"] = car.engine.driveline;
        carJson["Engine Information"]["Engine Type"] = car.engine.type;
        carJson["Engine Information"]["Hybrid"] = car.engine.hybrid;
        carJson["Engine Information"]["Number of Forward Gears"] = car.engine.gears;
        carJson["Engine Information"]["Transmission"] = car.engine.transmission;
        carJson["Engine Information"]["Engine Statistics"]["Horsepower"] = car.engine.stats.horsepower;
        carJson["Engine Information"]["Engine Statistics"]["Torque"] = car.engine.stats.torque;

        carJson["Fuel Information"]["City mpg"] = car.fuel.mpg_city;
        carJson["Fuel Information"]["Fuel Type"] = car.fuel.type;
        carJson["Fuel Information"]["Highway mpg"] = car.fuel.mpg_highway;

        carJson["Identification"]["Classification"] = car.iden.classification;
        carJson["Identification"]["ID"] = car.iden.id;
        carJson["Identification"]["Make"] = car.iden.make;
        carJson["Identification"]["Model Year"] = car.iden.model_year;
        carJson["Identification"]["Year"] = car.iden.year;

        resultsJson.push_back(carJson);
    }

    ofstream outFile("results.json");
    outFile << resultsJson.dump(4);
    outFile.close();

    // add time to time.json
    json timeJson;
    timeJson["Time"] = time;
    ofstream timeFile("time.json");
    timeFile << timeJson.dump(4);
    timeFile.close();
}

bool horsepowerFunc(Car car1, Car car2) {
    return car1.engine.stats.horsepower > car2.engine.stats.horsepower;
}

bool MPGFunc(Car car1, Car car2) {
    return car1.fuel.mpg_city > car2.fuel.mpg_city;
}


bool yearFunc(Car car1, Car car2) {
    return car1.iden.year > car2.iden.year;
}

// convert brand int into brand string
string getBrandName(int brand) {
    string brandName;

    if (brand == -1) {
        brandName = "";
    }
    else if (brand == 1) {
        brandName = "Honda";
    }
    else if (brand == 2) {
        brandName = "Toyota";
    }
    else if (brand == 3) {
        brandName = "Ford";
    }
    else if (brand == 4) {
        brandName = "Volkswagen";
    }
    else if (brand == 5) {
        brandName = "Hyundai";
    }
    else if (brand == 6) {
        brandName = "Nissan";
    }
    else if (brand == 7) {
        brandName = "Kia";
    }
    else if (brand == 8) {
        brandName = "Chevrolet";
    }
    
    return brandName;
}



// check if car meets requirements
bool isValid(Car car, int year, int horsePower1, int horsePower2, int gasMileage1, int gasMileage2, int driveline, string brandName) {
    bool valid = true;

    if (year != -1 && car.iden.year != year) {
        valid = false;
    }
    if (horsePower1 != -1 && car.engine.stats.horsepower < horsePower1) {
        valid = false;
    }
    if (horsePower2 != -1 && car.engine.stats.horsepower > horsePower2) {
        valid = false;
    }
    if (gasMileage1 != -1 && car.fuel.mpg_city < gasMileage1) {
        valid = false;
    }
    if (gasMileage2 != -1 && car.fuel.mpg_city > gasMileage2) {
        valid = false;
    }
    if (driveline == 1 && !(car.engine.driveline == "All-wheel drive" || car.engine.driveline == "Four-wheel drive")) {
        valid = false;
    }
    if (driveline == 2 && car.engine.driveline != "Front-wheel drive") {
        valid = false;
    }
    if (driveline == 3 && car.engine.driveline != "Rear-wheel drive") {
        valid = false;
    }
    if (!brandName.empty() && car.iden.make != brandName) {
        valid = false;
    }
    

    return valid;
}

int main() {
    vector<Car> cars = readJson("cars.json");

    unordered_map<string, json> sortingReqs = readSortingRequirements("requirements.json");

    int isBPlus = sortingReqs["isB++"];
    int year = sortingReqs["year"];
    int sortBy = sortingReqs["sortby"];
    int horsePower1 = sortingReqs["horsepow1"];
    int horsePower2 = sortingReqs["horsepow2"];
    int gasMileage1 = sortingReqs["gasmileage1"];
    int gasMileage2 = sortingReqs["gasmileage2"];
    int driveline = sortingReqs["driveline"];
    int brand = sortingReqs["Brand"];

    // get brand requirement

    string brandName = getBrandName(brand);

    // get operation to sort by
    bool (*operation)(Car, Car);
    if (sortBy == 1){
        operation = horsepowerFunc;
    }
    else if (sortBy == 2) {
        operation = MPGFunc;
    }
    else if (sortBy == 3) {
        operation = yearFunc;
    }
    else {
        throw runtime_error("sortBy is not valid");
    }

    // if user wants B++ tree
    if (isBPlus == 0) {

        //start timer
        auto start = chrono::high_resolution_clock::now();

        // make BPlus tree
        BPlus tree(operation);
        for (const Car car : cars) {

            tree.insert(car);
        }

        // get the top five cars
        vector<Car> topCars;
        
        Node* curr = tree.getHead();

        while (curr != nullptr && topCars.size() < 5) {
            for (int i = 0; i < curr->arr.size() && topCars.size() < 5; i++) {
                Car car = curr->arr[i];
                // check if car meet requirements
                if (isValid(car, year, horsePower1, horsePower2, gasMileage1, gasMileage2, driveline, brandName)) {
                    topCars.push_back(car);
                }
            }
            curr = curr->next;
        }
        

        // get time taken to sort cars
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;
        string time = "Time using B+ tree: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count()) + " ms";

        // write the top five cars to results.json
        writeResults(topCars, time, "results.json");
    }
    // if user wants heap
    else {
        auto start = chrono::high_resolution_clock::now();

        // make heap data
        Heap heap(operation);
        for (const Car& car : cars) {
            heap.insert(car);
        }

        // get the top five cars
        vector<Car> topCars;
        for (int i = 0; i < cars.size() && topCars.size() < 5; i++) {
            Car car = heap.extract();

            if (isValid(car, year, horsePower1, horsePower2, gasMileage1, gasMileage2, driveline, brandName)) {
                topCars.push_back(car);
            }
        }
        
        

        

        // get time taken to sort cars
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;
        string time = "Time using heap: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count()) + " ms";

        // write the top five cars to results.json
        writeResults(topCars, time, "results.json");
    }

    

    return 0;
} 