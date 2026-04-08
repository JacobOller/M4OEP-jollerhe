//
// Created by jacob on 2/1/2026.
// Class to control the different statistical data from house data.
//

#ifndef M1OEP_HOUSESTATISTICS_H
#define M1OEP_HOUSESTATISTICS_H

#include <map>

#include "HouseManager.h"

class HouseStatistics {
private:
    int mean_price = 0;
    int mean_size = 0;
    double mean_acreage = 0.0;
    int max_price = 0;
    int max_size = 0;
    double max_acreage = 0;
    int num_brokers = 0;
    int mean_broker_values = 0;
    int max_broker_value = 0;
    int valid_zipcodes = 0;
    std::string max_broker_id = "";

public:
    HouseStatistics();

    /**
     * Method to calculate the mean values for:
     * house price, house size, and house acreage size.
     * @param house_manager house manager object
     */
    void calculate_mean_values(HouseManager &house_manager);
    /**
     * Method to calculate the max values for:
     * house price, house size, and house acreage size.
     */
    void calculate_max_values(HouseManager &house_manager);
    /**
     * Method to calculate broker data:
     * mean for the amount of listings per broker, max number of occurrences of a broker.
     */
    void calculate_broker_values(HouseManager &house_manager);

    // Getters
    int get_mean_price() const;
    int get_mean_size() const;
    double get_mean_acreage() const;
    int get_num_brokers() const;
    int get_mean_broker_values() const;
    int get_max_broker_value() const;
    int get_num_valid_zipcodes() const;

    // Calculates valid zipcodes. A zipcode is valid if it appears at least as many times as the threshold.
    // This is important because if a zipcode shows up less than the threshold, then it will not be good for training AI.
    // For example, if a zipcode only has 2 house objects, these could be complete outliers for that given zip code.
    // A threshold in this context is similar to a minimum sample size (usually 30) in statistics is used to prevent variance.
    int calculate_valid_zipcodes(const std::vector<House> &houses, int threshold);

    /**
     * Method to print stats info to the console.
     */
    void print_stat_info() const;
};
#endif //M1OEP_HOUSESTATISTICS_H