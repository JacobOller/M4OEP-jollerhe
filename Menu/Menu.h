//
// Created by jacob on 2/2/2026.
//

#ifndef M1OEP_MENU_H
#define M1OEP_MENU_H

#include "../HouseObjects/House.h"
#include "../HouseObjects/HouseStatistics.h"
#include "../HouseObjects/HouseManager.h"
#include <vector>


class Menu {
private:
public:
    void print_menu(HouseStatistics &stats, HouseManager &house_manager);
    void choose_option(HouseStatistics &stats, HouseManager &house_manager);
    std::vector<House> find_my_budget();
    int find_average_price();

};
#endif //M1OEP_MENU_H