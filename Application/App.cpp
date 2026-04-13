//
// Created by jacob on 3/31/2026.
//

#include "Application/App.h"
#include "Pipeline/DataPipeline.h"
#include <iostream>
#include <string>

void App::run() {
    std::cout << "Welcome to my Real Estate Program!\n";

    const std::string csvPath = "./data/realtor_data.csv";
    const std::string jsonPath = "./data/clean_house_data.json";
    std::cout << "Loading, sorting, computing statistics, and exporting JSON…\n";

    std::string err;
    if (!DataPipeline::run(hm, stats, csvPath, jsonPath, err)) {
        std::cout << err << "\n";
        std::cout << "Place realtor_data.csv in the data folder (project root ./data/).\n";
        return;
    }

    std::cout << "Successfully wrote " << hm.get_num_of_houses() << " valid houses to the vector\n";
    std::cout << "Avoided writing " << hm.get_invalid_count() << " invalid data values\n";
    std::cout << "Avoided writing " << hm.get_outlier_count() << " outlier data values\n\n";

    menu.print_menu(stats, hm);
}
