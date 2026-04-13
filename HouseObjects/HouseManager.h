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
    std::vector<House> houses_by_location;
    std::vector<House> houses_search;
    long invalid_count = 0;
    long outlier_count = 0;
public:
    HouseManager();
    // Method to get all the house data from the file
    bool data_from_file(std::string fileName);
    void calculate_houses_in_budget(int lower, int upper);
    void calculate_houses_in_city(std::string city, std::string state);
    /// At least one of zip, city, state must be non-empty after trimming. AND semantics for non-empty fields.
    /// City and state matching is case-insensitive; zip is exact (trimmed).
    bool filter_by_location(const std::string &zip, const std::string &city, const std::string &state);
    /// Empty field = ignore. At least one field must be set. Returns false if all empty or a numeric field is invalid.
    bool filter_by_search(const std::string &zip, const std::string &city, const std::string &state,
                          const std::string &bedsStr, const std::string &bathsStr, const std::string &sqftStr);
    // Getters
    std::vector<House> &get_houses_vector(); // Not const because we are modifying it with heap sort
    const long get_invalid_count();
    const long get_outlier_count();
    const long get_num_of_houses();
    const std::vector<House> get_houses_in_budget();
    const std::vector<House> get_houses_in_city();
    const std::vector<House> &get_houses_in_budget_ref() const;
    const std::vector<House> &get_houses_by_location_ref() const;
    const std::vector<House> &get_houses_search_ref() const;
    // Method to print title for the house data
    void print_title();
    // Method to print house data
    void print_houses(std::vector<House> &houses, int start, int max);

    void export_data(const std::string &filename);
};
#endif //M1OEP_HOUSEMANAGER_H
