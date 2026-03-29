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

    /**
     * Method to print stats info to the console.
     */
    void print_stat_info() const;
};
#endif //M1OEP_HOUSESTATISTICS_H