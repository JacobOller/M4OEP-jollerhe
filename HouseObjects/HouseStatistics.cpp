//
// Created by jacob on 2/1/2026.
//

#include "./HouseStatistics.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

HouseStatistics::HouseStatistics() {
    mean_price = 0;
    mean_size = 0;
    mean_acreage = 0.0;
}
void HouseStatistics::calculate_mean_values(HouseManager &house_manager) {
    if (house_manager.get_num_of_houses() == 0) {
        mean_price = mean_size = 0;
        mean_acreage = 0.0;
        return;
    }
    long long total_prices = 0;
    long long total_sizes = 0;
    double total_acreages = 0;
    for (int i = 0; i < house_manager.get_num_of_houses(); i++) {
        total_prices += house_manager.get_houses_vector()[i].get_price();
        total_sizes += house_manager.get_houses_vector()[i].get_house_size();
        total_acreages += house_manager.get_houses_vector()[i].get_size_in_acres();
    }
    mean_price = total_prices / house_manager.get_num_of_houses();
    mean_size = total_sizes / house_manager.get_num_of_houses();
    mean_acreage = total_acreages / house_manager.get_num_of_houses();
}
void HouseStatistics::calculate_max_values(HouseManager &house_manager) {
    for (int i = 0; i < house_manager.get_num_of_houses(); i++) {
        if (house_manager.get_houses_vector()[i].get_price() > max_price)
            max_price = house_manager.get_houses_vector()[i].get_price();
        if (house_manager.get_houses_vector()[i].get_house_size() > max_size)
            max_size = house_manager.get_houses_vector()[i].get_house_size();
        if (house_manager.get_houses_vector()[i].get_size_in_acres() > max_acreage)
            max_acreage = house_manager.get_houses_vector()[i].get_size_in_acres();
    }
}
void HouseStatistics::calculate_broker_values(HouseManager &house_manager) {
    std::map<std::string, int> broker_occurrences;
    // Loop to create a mapping of keys (broker IDS) to values (number of occurrences)
    for (int i = 0; i < house_manager.get_num_of_houses(); i++) {
        const House &house = house_manager.get_houses_vector()[i];
        broker_occurrences[house.get_brokered_by()]++;
    }
    long total_broker_values = 0;
    // Loop to find the mean broker value
    // [Key] is the Broker ID
    // [Value] is the number of occurrences
    for (auto const& [key, value] : broker_occurrences) {
        total_broker_values += value;
    }
    // Loop to find the broker with the max value
    for (auto const& [id, value] : broker_occurrences) {
        if (value > max_broker_value) {
            max_broker_value = value;
            max_broker_id = id;
        }
    }
    if (broker_occurrences.empty()) {
        mean_broker_values = 0;
        num_brokers = 0;
        return;
    }
    mean_broker_values = total_broker_values / broker_occurrences.size();
    num_brokers = broker_occurrences.size();
}
int HouseStatistics::get_mean_price() const {
    return mean_price;
}
int HouseStatistics::get_mean_size() const {
    return mean_size;
}
double HouseStatistics::get_mean_acreage() const {
    return mean_acreage;
}
int HouseStatistics::get_num_brokers() const {
    return num_brokers;
}
int HouseStatistics::get_mean_broker_values() const {
    return mean_broker_values;
}
int HouseStatistics::get_max_broker_value() const {
    return max_broker_value;
}
int HouseStatistics::get_num_valid_zipcodes() const {
    return valid_zipcodes;
}

int HouseStatistics::calculate_valid_zipcodes(const std::vector<House> &houses, int threshold) {
    // Create an unordered set, because you can only insert unique elements into the set,
    // meaning that inserting a duplicate does not work.
    std::unordered_map<std::string, int> seen_zipcodes;
    for (const auto &house : houses) {
        seen_zipcodes[house.get_zip_code()]++;
    }
    for (auto const& [key, value] : seen_zipcodes) {
        if (value >= threshold)
            valid_zipcodes++;
    }
    return valid_zipcodes;
}
void HouseStatistics::calculate_city_values(const std::vector<House> &houses) {
    // Maps each city and state pair to a total price and number of occurrences pair
    // Map format: <(city, state), (total price, occurrences)>
    std::map<std::pair<std::string, std::string>, std::pair<double, int>> cities;
    for (const auto& house : houses) {
        std::pair key = std::make_pair(house.get_city(), house.get_state());
        // Use .first and .second, which access the first/second elements of the (total price, occurrences) pair
        cities[key].first += house.get_price();
        cities[key].second++;
    }
    // Calculate the mean average for each key (city). Cities[key].first becomes the mean average price for that key (city)
    for (auto& [key, value] : cities) {
        value.first = value.first / value.second;
    }
    city_values = cities;
}
int HouseStatistics::get_num_houses_in_city(const std::string& city, const std::string& state) const {
    std::pair<std::string, std::string> key = std::make_pair(city, state);
    auto iter = city_values.find(key);
    // If the value points to end, then that means it didn't find the city.
    if (iter != city_values.end()) {
        return iter->second.second;
    }
    return 0;
}

void HouseStatistics::print_stat_info() const {
    std::cout << "-----------------------" << std::endl;
    std::cout << "     HOUSE INFO     " << std::endl;
    std::cout << "Price Info:" << std::endl;
    std::cout << "   Mean Price: $" << mean_price << std::endl;
    std::cout << "   Max Price: $" << max_price << std::endl;
    std::cout << "Size Info:" << std::endl;
    std::cout << "   Mean Size: " << mean_size << " sqft" << std::endl;
    std::cout << "   Max Size: " << max_size << " sqft" << std::endl;
    std::cout << "Acreage Info:" << std::endl;
    std::cout << "Mean Acreage: " << std::fixed << std::setprecision(4) << mean_acreage << " acres" << std::endl;
    std::cout << "   Max Acreage: " << max_acreage << " acres" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "    BROKER INFO    " << std::endl;
    std::cout << "Total number of brokers: " << num_brokers << " brokers" << std::endl;
    std::cout << "Mean for the amount of listings per broker: " << mean_broker_values << " listings" << std::endl;
    std::cout << "Max amount of listings by one broker: " << max_broker_value << " from the Broker with the ID: " << max_broker_id << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "   LOCATION INFO   " << std::endl;
    std::cout << "Number of unique zipcodes above the threshold: " << valid_zipcodes << std::endl;
    std::cout << "Number of houses in NORTON: " << get_num_houses_in_city("Norton", "Massachusetts");
}