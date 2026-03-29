//
// Created by jacob on 2/21/2026.
//

#include <iostream>

#include "HouseObjects/House.h"
#include "HouseObjects/HouseManager.h"
#include "HouseObjects/HouseStatistics.h"


bool test_house();
bool test_house_manager();
bool test_house_statistics();

int main() {
    if (test_house()) {
        std::cout << "All House test cases passed" << std::endl;
    }
    if (test_house_manager()) {
        std::cout << "All House Manager test cases passed" << std::endl;
    }
    if (test_house_statistics()) {
        std::cout << "All House Statistics test cases passed" << std::endl;
    }
    return 0;
}

bool test_house() {
    bool passed = true;
    House h;
    if (h.get_brokered_by() != "" && h.get_status() != "" && h.get_price() != -1 &&
         h.get_beds() != -1 && h.get_baths() != -1 && h.get_size_in_acres() != -1.0 &&
         h.get_street_id() != "" && h.get_city() != "" && h.get_state() != "" &&
         h.get_zip_code() != "" && h.get_house_size() != -1 && h.get_prev_sold_date() != "") {
        std::cout << "FAILED default constructor test case" << std::endl;
        passed = false;
    }
    House h2("10245.0", "for_sale", 500000, 3, 2, .2, "513915814",
        "Houston", "Texas", "02765", 2200, "9/12/19");
    if (h2.get_brokered_by() != "10245.0" && h2.get_status() != "for_sale" && h2.get_price() != 500000 &&
        h2.get_beds() != 3 && h2.get_baths() != 2 && h2.get_size_in_acres() != .2 &&  h2.get_street_id() != "513915814" &&
            h2.get_city() != "Houston" && h2.get_state() != "Texas" && h2.get_zip_code() != "02765"
            && h2.get_house_size() != 2200 && h2.get_prev_sold_date() != "2019-05-04") {
        std::cout << "FAILED custom constructor test case" << std::endl;
        passed = false;
    }
    h2.set_brokered_by("10246.0");
    h2.set_status("for_sale");
    h2.set_price(600000);
    h2.set_beds(3);
    h2.set_baths(2);
    h2.set_size_in_acres(.5);
    h2.set_street_id("513915854");
    h2.set_city("Houston");
    h2.set_state("Texas");
    h2.set_zip_code("02765");
    h2.set_house_size(2400);
    h2.set_prev_sold_date("2021-06-25");
    if (h2.get_brokered_by() != "10246.0" && h2.get_status() != "for_sale" && h2.get_price() != 600000 &&
        h2.get_beds() != 3 && h2.get_baths() != 2 && h2.get_size_in_acres() != .2 &&  h2.get_street_id() != "513915854" &&
            h2.get_city() != "Houston" && h2.get_state() != "Texas" && h2.get_zip_code() != "02765"
            && h2.get_house_size() != 2400 && h2.get_prev_sold_date() != "2021-06-25") {
        std::cout << "FAILED setter test case" << std::endl;
        passed = false;
    }
    return passed;
}

bool test_house_manager() {
    bool passed = true;
    HouseManager hm;
    hm.data_from_file("../data/test_data.csv");

    if (hm.get_num_of_houses() != 3) {
        std::cout << "FAILED get_num_of_houses method test case" << std::endl;
        passed = false;
    }
    HouseManager hm2;
    hm2.data_from_file("../data/bad_test_data.csv");
    if (hm2.get_invalid_count() != 12) {
        std::cout << hm2.get_invalid_count() << std::endl;
        std::cout << "FAILED get_invalid_count method test case" << std::endl;
        passed = false;
    }
    if (hm2.get_outlier_count() != 3) {
        std::cout << "FAILED get_outlier_count method test case" << std::endl;
        passed = false;
    }
    return passed;
}

bool test_house_statistics() {
    bool passed = true;
    HouseStatistics hs;
    HouseManager hm;

    hm.data_from_file("../data/test_data.csv");
    hs.calculate_mean_values(hm);
    hs.calculate_max_values(hm);

    if (hs.get_mean_price() != 200000 && hs.get_mean_size() != 1500 && hs.get_mean_acreage() != .10) {
        std::cout << "FAILED mean method test case" << std::endl;
        passed = false;
    }
    return passed;
}
