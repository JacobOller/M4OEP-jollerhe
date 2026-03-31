//
// Created by jacob on 1/27/2026.
//

#include "HouseObjects/HouseManager.h"
#include "Menu/Menu.h"
#include "Sorting/HeapSort.h"

#include <string>
#include <iostream>
#include <iomanip>

int main() {
    std::cout << "Welcome to my Real Estate Program!" << std::endl;
    // Create house manager object to control all the houses
    HouseManager house_manager;
    const std::string file_name = "./data/realtor_data.csv";
    std::cout << "Now Opening the File Provided and Writing the Data to a Vector..." << std::endl;
    house_manager.data_from_file(file_name);
    std::cout << "Successfully wrote " << house_manager.get_num_of_houses() << " Valid Houses to the Vector" << std::endl;
    std::cout << "Avoided Writing " << house_manager.get_invalid_count() << " Invalid Data Values" << std::endl;
    std::cout << "Avoided Writing " << house_manager.get_outlier_count() << " Outlier Data Values" << std::endl << std::endl;

    std::cout << "Now Sorting Data and Calculating Statistical Information..." << std::endl;
    unsigned long reads,allocations = 0;
    // Sort data with heap sort algorithm
    HeapSort::heapSort(house_manager.get_houses_vector(), reads, allocations);
    // Call statistical methods now during loading phase
    HouseStatistics stats;
    stats.calculate_mean_values(house_manager);
    stats.calculate_max_values(house_manager);
    stats.calculate_broker_values(house_manager);

    // Write the data to a csv file in order to train the AI model in ai_training.py
    house_manager.export_data("./data/clean_house_data.csv");

    // Create menu to list out user options
    Menu menu;
    menu.print_menu(stats, house_manager);


    return 0;
}
