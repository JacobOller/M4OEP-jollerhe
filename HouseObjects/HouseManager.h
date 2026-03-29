//
// Created by jacob on 2/1/2026.
// Class to handle file control, then the corresponding houses vector.
//

#ifndef M1OEP_HOUSEMANAGER_H
#define M1OEP_HOUSEMANAGER_H

#include "House.h"
#include <vector>

class HouseManager {
private:
    std::vector<House> houses;
    std::vector<House> houses_in_budget;
    std::vector<House> houses_in_city;
    long invalid_count = 0;
    long outlier_count = 0;
public:
    HouseManager();
    // Method to get all the house data from the file
    bool data_from_file(std::string fileName);
    // Getters
    std::vector<House> &get_houses_vector(); // Not const because we are modifying it with heap sort
    std::vector<House> get_houses_in_budget(int lower, int upper);
    std::vector<House> get_houses_in_city(std::string city, std::string state);
    const long get_invalid_count();
    const long get_outlier_count();
    const long get_num_of_houses();
    // Method to print title for the house data
    void print_title();
    // Method to print house data
    void print_houses(std::vector<House> &houses, int start, int max);
};
#endif //M1OEP_HOUSEMANAGER_H
