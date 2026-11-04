#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include "cars.h"
#include "heap.h"
#include <json.hpp>
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
unordered_map<string, string> readSortingRequirements(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("could not open: " + filename);
    }

    unordered_map<string, string> sortingReqs;
    json reqsData; 
    file >> reqsData;

    for (auto& [key, value] : reqsData.items()) {
        sortingReqs[key] = value;
    }

    return sortingReqs;


}

int main() {
    vector<Car> cars = readJson("cars.json");

    unordered_map<string, string> sortingReqs = readSortingRequirements("requirements.json");

    string dataStructure = sortingReqs["data_structure"];

    if (dataStructure == "B+") {
        auto start = chrono::high_resolution_clock::now();

        // make B+ data

        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;

        string time = "Time using B+ tree: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count());
    }
    else if (dataStructure == "heap") {
        auto start = chrono::high_resolution_clock::now();

        // make heap data

        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;

        string time = "Time using a heap: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count());
    }

    

    //put the top n cars into another json file so front end can read them
    

    return 0;
} 