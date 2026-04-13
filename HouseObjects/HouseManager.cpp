//
// Created by jacob on 2/1/2026.
//

#include "./HouseManager.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

const long long MAX_PRICE = 20000000;
const int MIN_PRICE = 50000;
const int MAX_SIZE = 15000;
const int MIN_SIZE = 500;
const double MAX_ACREAGE = 5.0;
const int MIN_ACREAGE = .01;

// Note: Gemini helped me with the following 3 functions, as it related to
//  Qt's string validation which was tricky. I tried to implement this entirely on my own,
// but Gemini gave me a lot of optimal solutions that I have never thought of before.
// Note: the follpowing functions are static because they are only used within this file,
// and don't use any private variables from the HouseManager class.

// Helper for parse_optional_int function and filter_by_location function
static std::string trim_copy(const std::string &s) {
    const int start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    const int end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
// Helper for parse_optional_int function
static bool iequals(const std::string &first, const std::string &second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); ++i) {
        char first_c = first[i];
        char second_c = second[i];
        if (std::tolower(first_c) != std::tolower(second_c)) {
            return false;
        }
    }
    return true;
}

static bool parse_optional_int(const std::string &raw, int &value, bool &specified) {
    const std::string trimmed = trim_copy(raw);
    if (trimmed.empty()) {
        specified = false;
        return true;
    }
    try {
        std::size_t pos = 0;
        value = std::stoi(trimmed, &pos);
        if (pos != trimmed.size()) {
            return false;
        }
        specified = true;
        return true;
    } catch (const std::exception &) {
        return false;
    }
}

HouseManager::HouseManager() {
    invalid_count = 0;
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
void HouseManager::calculate_houses_in_budget(int lower, int upper) {
    houses_in_budget.clear();
    for (int i = 0; i < houses.size(); i++) {
        if (houses[i].get_price() >= lower && houses[i].get_price() <= upper) {
            houses_in_budget.push_back(houses[i]);
        }
    }
}
void HouseManager::calculate_houses_in_city(std::string city, std::string state) {
    houses_in_city.clear();
    // std::transform(city.begin(), city.end(), city.begin(),::toupper);
    // std::transform(state.begin(), state.end(), state.begin(),::toupper);
    for (int i = 0; i < houses.size(); i++) {
        if ((houses[i].get_city() == city) && (houses[i].get_state() == state)) {
            houses_in_city.push_back(houses[i]);
        }
    }
}

bool HouseManager::filter_by_location(const std::string &zip, const std::string &city,
                                        const std::string &state) {
    houses_by_location.clear();
    std::string z = trim_copy(zip);
    std::string c = trim_copy(city);
    std::string st = trim_copy(state);
    if (z.empty() && c.empty() && st.empty()) {
        return false;
    }
    for (int i = 0; i < houses.size(); i++) {
        House &h = houses[i];
        if (!z.empty() && h.get_zip_code() != z) {
            continue;
        }
        if (!c.empty() && !iequals(h.get_city(), c)) {
            continue;
        }
        if (!st.empty() && !iequals(h.get_state(), st)) {
            continue;
        }
        houses_by_location.push_back(h);
    }
    return true;
}

// Note: Gemini gave me the idea to use parse_optional_int for the search function, as it was a lot easier to implement than my own solution.
bool HouseManager::filter_by_search(const std::string &zip, const std::string &city, const std::string &state,
            const std::string &bedsStr, const std::string &bathsStr,
            const std::string &sqftStr) {
    houses_search.clear();
    const std::string z = trim_copy(zip);
    const std::string c = trim_copy(city);
    const std::string st = trim_copy(state);
    int beds_value = 0;
    int baths_value = 0;
    int sqft_value = 0;
    bool has_beds = false;
    bool has_baths = false;
    bool has_sqft = false;
    if (!parse_optional_int(bedsStr, beds_value, has_beds)) {
        return false;
    }
    if (!parse_optional_int(bathsStr, baths_value, has_baths)) {
        return false;
    }
    if (!parse_optional_int(sqftStr, sqft_value, has_sqft)) {
        return false;
    }
    if (z.empty() && c.empty() && st.empty() && !has_beds && !has_baths && !has_sqft) {
        return false;
    }
    for (int i = 0; i < houses.size(); i++) {
        House &h = houses[i];
        if (!z.empty() && h.get_zip_code() != z) {
            continue;
        }
        if (!c.empty() && !iequals(h.get_city(), c)) {
            continue;
        }
        if (!st.empty() && !iequals(h.get_state(), st)) {
            continue;
        }
        if (has_beds && h.get_beds() != beds_value) {
            continue;
        }
        if (has_baths && h.get_baths() != baths_value) {
            continue;
        }
        if (has_sqft && h.get_house_size() != sqft_value) {
            continue;
        }
        houses_search.push_back(h);
    }
    return true;
}

std::vector<House> &HouseManager::get_houses_vector() {
    return houses;
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
const std::vector<House> HouseManager::get_houses_in_budget() {
    return houses_in_budget;
}
const std::vector<House> HouseManager::get_houses_in_city() {
    return houses_in_city;
}

const std::vector<House> &HouseManager::get_houses_in_budget_ref() const {
    return houses_in_budget;
}

const std::vector<House> &HouseManager::get_houses_by_location_ref() const {
    return houses_by_location;
}

const std::vector<House> &HouseManager::get_houses_search_ref() const {
    return houses_search;
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
    // Open the json array
    file << "[\n";

    for (unsigned long i = 0; i < houses.size(); ++i) {

        // Open the json object
        file << "  {\n";

        // Write the key and value pairs
        file << "    \"price\": " << houses[i].get_price() << ",\n";
        file << "    \"beds\": " << houses[i].get_beds() << ",\n";
        file << "    \"baths\": " << houses[i].get_baths() << ",\n";
        file << "    \"size_in_acres\": " << houses[i].get_size_in_acres() << ",\n";
        file << "    \"house_size\": " << houses[i].get_house_size() << ",\n";
        // Use quotes for zip code because as an int it will lose the 0.
        file << "    \"zip_code\": \"" << houses[i].get_zip_code() << "\"\n";

        // Close the json object
        file << "  }";

        // 3. Add a comma only if it is not the last item in the list
        if (i != houses.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    // Close the json array
    file << "]\n";

    file.close();
    std::cout << "Successfully exported clean json data." << std::endl;
}
