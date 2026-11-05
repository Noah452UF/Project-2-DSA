#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include "cars.cpp"
#include "heap.cpp"
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
    json resultsJson;
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

int main() {
    vector<Car> cars = readJson("cars.json");

    unordered_map<string, json> sortingReqs = readSortingRequirements("requirements.json");

    bool isBPlus = sortingReqs["isB++"];
    string sortBy = sortingReqs["sortby"];
    int horsePower1 = sortingReqs["horsepow1"];
    int horsePower2 = sortingReqs["horsepow2"];
    int gasMileage1 = sortingReqs["gasmileage1"];
    int gasMileage2 = sortingReqs["gasmileage2"];
    string driveLine = sortingReqs["driveline"];
    string brand = sortingReqs["Brand"];

    // if user wants B++ tree
    if (isBPlus) {
        auto start = chrono::high_resolution_clock::now();

        // make B++ data
        vector<Car> BPlusTreeCars;

        // get the top five cars
        vector<Car> topCars;
        for (int i = 0; i < 5; i++) {
            topCars.push_back(BPlusTreeCars[i]);
        }
        
        // get time taken to sort cars
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;
        string time = "Time using B+ tree: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count());

        // write the top five cars to results.json
        writeResults(topCars, time, "results.json");
    }
    // if user wants heap
    else {
        auto start = chrono::high_resolution_clock::now();

        // make heap data
        vector<Car> heapCars;

        // get the top five cars
        vector<Car> topCars;
        for (int i = 0; i < 5; i++) {
            topCars.push_back(heapCars[i]);
        }
        
        // get time taken to sort cars
        auto end = chrono::high_resolution_clock::now();
        auto duration = end - start;
        string time = "Time using heap: " + to_string(chrono::duration_cast<chrono::milliseconds>(duration).count());

        // write the top five cars to results.json
        writeResults(topCars, time, "results.json");
    }

    

    return 0;
} 