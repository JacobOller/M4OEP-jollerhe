//
// Created by jacob on 3/31/2026.
//

#ifndef M1OEP_APP_H
#define M1OEP_APP_H

#include "HouseObjects/HouseManager.h"
#include "Menu/Menu.h"

class App {
private:
    HouseManager hm;
    HouseStatistics stats;
    Menu menu;

public:
    void run();
};


#endif //M1OEP_APP_H