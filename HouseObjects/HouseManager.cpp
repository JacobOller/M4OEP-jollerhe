//
// Created by jacob on 2/1/2026.
//

#include "./HouseManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

const long long MAX_PRICE = 20000000;
const int MIN_PRICE = 50000;
const int MAX_SIZE = 15000;
const int MIN_SIZE = 500;
const double MAX_ACREAGE = 5.0;
const int MIN_ACREAGE = .01;

HouseManager::HouseManager() {
    invalid_count = 0; // Ensure this starts at zero!
    }

bool HouseManager::data_from_file(std::string file_name) {
    std::ifstream fileIn(file_name);

    if (!fileIn.is_open()) {
        std::cout << "Error opening file with the name: " << file_name << std::endl;
        return false;
    }

    std::string line;
    std::getline(fileIn, line); // Skip header

    while (std::getline(fileIn, line)) {
        std::stringstream stream(line);
        std::string segment;
        std::vector<std::string> rowData;

        while (std::getline(stream, segment, ',')) {
            rowData.push_back(segment);
        }
        // If the data doesn't have 12 rows, we skip and mark as invalid
        if (rowData.size() < 12) {
            invalid_count++;
            continue;
        }
        try {
            // Strings
            std::string brokered_by = rowData[0];
            std::string status = rowData[1];

            // Integers with validation (Check empty, then convert)
            // Note: Using stod->int cast to handle "1000.0" safely
            int price = (rowData[2].empty()) ? -1 : (int)std::stod(rowData[2]);
            int beds  = (rowData[3].empty()) ? -1 : (int)std::stod(rowData[3]);
            int baths = (rowData[4].empty()) ? -1 : (int)std::stod(rowData[4]);

            // Double
            double size_in_acres = (rowData[5].empty()) ? -1.0 : std::stod(rowData[5]);

            // Strings
            std::string street_id= rowData[6];
            std::string city = rowData[7];
            std::string state = rowData[8];
            std::string zip_code = rowData[9];

            // House Size
            int house_size = (rowData[10].empty()) ? -1 : (int)std::stod(rowData[10]);

            // Previous Sold Date
            std::string prev_sold_date = rowData[11];

            // If any of the data values were not present and are -1, increase invalid counter
            if (brokered_by.empty() || status.empty() || price == -1 || beds == -1 || baths == -1 || size_in_acres == -1.0 ||
                 street_id.empty() || city.empty() || state.empty() || zip_code.empty() || house_size == -1 || prev_sold_date.empty()) {
                invalid_count++;
                // Don't push back if invalid, instead continue
                continue;
            }
            // Cleaning the data to account for bad rows with price values that are way too low.
            // Get rid of outliers that are likely not houses
            if (price > MAX_PRICE || price < MIN_PRICE || house_size > MAX_SIZE || house_size < MIN_SIZE ||
                size_in_acres > MAX_ACREAGE || size_in_acres < MIN_ACREAGE) {
                outlier_count++;
                // Don't push back if an outlier, instead continue
                continue;
            }

            // Construct the object
            House house(brokered_by, status, price, beds, baths, size_in_acres,
                street_id, city, state, zip_code, house_size, prev_sold_date);

            // Push back valid data to the houses vector
            houses.push_back(house);
        }
        catch (const std::exception& e) {
            // Invalid data counter, meaning that a non prev_sold_date value is null
            invalid_count++;
            continue;
        }
    }
    fileIn.close();
    return true;
}
std::vector<House> &HouseManager::get_houses_vector() {
    return houses;
}
std::vector<House> HouseManager::get_houses_in_budget(int lower, int upper) {

    for (int i = 0; i < houses.size(); i++) {
        if (houses[i].get_price() >= lower && houses[i].get_price() <= upper) {
            houses_in_budget.push_back(houses[i]);
        }
    }
    return houses_in_budget;
}
std::vector<House> HouseManager::get_houses_in_city(std::string city, std::string state) {
    // std::transform(city.begin(), city.end(), city.begin(),::toupper);
    // std::transform(state.begin(), state.end(), state.begin(),::toupper);
    for (int i = 0; i < houses.size(); i++) {
        if ((houses[i].get_city() == city) && (houses[i].get_state() == state)) {
            houses_in_city.push_back(houses[i]);
        }
    }
    return houses_in_city;
}

const long HouseManager::get_invalid_count() {
    return invalid_count;
}
const long HouseManager::get_outlier_count() {
    return outlier_count;
}
const long HouseManager::get_num_of_houses() {
    return houses.size();
}

void HouseManager::print_houses(std::vector<House> &houses, int start, int max) {

    // Title Columns
    std::cout << std::left  << std::setw(7)  << "NUM"
    << std::left << std::setw(10) << "BRKR_ID"
    << "   " << std::left << std::setw(8) << "PRICE"
    << std::left << std::setw(5)  << "BEDS"
    << std::right << std::setw(5)  << "BATHS"
    << " " << std::left << std::setw(7)  << "ACRES"
    << std::right << std::setw(7) << "STATE"
    << std::right << std::setw(16) << "CITY"
    << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    // Loop through data values to print
    for (int i = start; i < start + max; i++) {
        std::cout << "#" << i + 1 << ": " << houses[i] << std::endl;
    }
}

void HouseManager::export_data(const std::string &filename) {
    std::ofstream file(filename);

    // Write the header row so python pandas knows what the columns are
    file << "price,beds,baths,size_in_acres,house_size,zip_code\n";

    //
    for (const auto& house : houses) {
        file << house.get_price() << ","
             << house.get_beds() << ","
             << house.get_baths() << ","
             << house.get_size_in_acres() << ","
             << house.get_house_size() << ","
             << house.get_zip_code() << "\n";
    }

    file.close();
    std::cout << "Successfully exported clean data for AI training." << std::endl;
}
