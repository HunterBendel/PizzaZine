#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// This struct defines all of the data that will be pulled from each line of the csv file
struct Location {
    string name;
    string address;
    string city;
    long postalCode;
    string province;
    double latitude;
    double longitude;
    int priceRangeMin;
    int priceRangeMax;
};

// This class holds the vector as well as some member functions
class PizzaZine {
private:
    // This vector stores the data read in from the csv file
    vector <Location> locations;

public:
    // Class constructor
    PizzaZine() = default;
    // Sets up a size function to draw out the total size of the vector
    size_t size() const;
    // This function reads in the csv file to the class
    void readInFile(const string&, size_t);
    // This function returns data from a certain index in the vector
    Location& operator[](size_t);
    // This function adds new data at a new index in the vector.
    void add(Location new_location);
    // This function also returns data from a certain index in the vector
    Location& get(size_t);
    // This function returns data from the first index in the vector
    Location& first();
    // This function returns data from the last index in the vector
    Location& last();

};

void PizzaZine::readInFile(const string& filename,size_t c) {
    std::ifstream inFile(filename);
    Location newLoc;

    string line;
    string cell;

    // Read each line
    for (size_t i = 0; i < c; ++i) {
        // Break each line up into 'cells'
        getline(inFile, line);
        std::stringstream lineStream(line);
        while(getline(lineStream, newLoc.name, ',')) {
            getline(lineStream, newLoc.address, ',');
            getline(lineStream, newLoc.city, ',');
            getline(lineStream, cell, ',');
            if (!cell.empty()) {
                newLoc.postalCode = stoul(cell);
            }

            getline(lineStream, newLoc.province, ',');
            getline(lineStream, cell, ',');
            newLoc.latitude = stod(cell);
            getline(lineStream, cell, ',');
            newLoc.longitude = stod(cell);

            newLoc.priceRangeMin = -1;
            getline(lineStream, cell, ',');
            if (!cell.empty()) {
                newLoc.priceRangeMin = stoul(cell);
            }

            newLoc.priceRangeMax = -1;
            getline(lineStream, cell, ',');
            if (!cell.empty() && cell != "\r") {
                newLoc.priceRangeMax = stoul(cell);
            }
            add(newLoc);
        }
    }
}

size_t PizzaZine::size() const {
    return locations.size();
}

Location& PizzaZine::get(size_t index) {
    return locations.at(index);
}

Location& PizzaZine::operator[](size_t index) {
    return locations.at(index);
}

void PizzaZine::add(Location new_location) {
    locations.push_back(new_location);
}

Location& PizzaZine::first() {
    return locations.at(0);
}

Location& PizzaZine::last() {
    return locations.at(locations.size() - 1);
}
