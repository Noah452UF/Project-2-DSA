#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
 // placeholder, carter might set up the file names differently
#include <json.hpp>
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

int main() {
    vector<Car> cars = readJson("cars.json");

    //get requirements for sorting from json file?

    // make B+ data structure with sorting requirements
    BPlus(bool (*operation)(car,car));

    // make heap data structure with sorting requirements
    Heap(bool (*operation)(car,car));

    //put the top n cars into another json file so front end can read them
    

    return 0;
} 