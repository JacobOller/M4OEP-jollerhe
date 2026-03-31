//
// Created by jacob on 3/31/2026.
//

#include "App.h"
#include "Sorting/HeapSort.h"
#include <string>
#include <iostream>
#include <iomanip>

void App::run() {
    std::cout << "Welcome to my Real Estate Program!\n";

    const std::string file_name = "./data/realtor_data.csv";
    std::cout << "Now Opening the File Provided and Writing the Data to a Vector...\n";
    hm.data_from_file(file_name);

    std::cout << "Successfully wrote " << hm.get_num_of_houses() << " Valid Houses to the Vector\n";
    std::cout << "Avoided Writing " << hm.get_invalid_count() << " Invalid Data Values\n";
    std::cout << "Avoided Writing " << hm.get_outlier_count() << " Outlier Data Values\n\n";

    std::cout << "Now Sorting Data and Calculating Statistical Information...\n";
    unsigned long reads = 0, allocations = 0;

    // Sort data with heap sort algorithm
    HeapSort::heapSort(hm.get_houses_vector(), reads, allocations);

    // Call statistical methods
    stats.calculate_mean_values(hm);
    stats.calculate_max_values(hm);
    stats.calculate_broker_values(hm);

    // Export the cleaned data for AI predictions
    hm.export_data("./data/clean_house_data.csv");

    // Launch the interactive menu
    menu.print_menu(stats, hm);
}
