//
// Created by jacob on 2/2/2026.
//

#include "../Menu/Menu.h"
#include <iostream>
#include <thread>

void Menu::print_menu(HouseStatistics &stats, HouseManager &house_manager) {
    std::cout << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(25, ' ') << "MENU" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "1.) General Statistical Summary" << std::endl;
    std::cout << "2.) Search by Budget" << std::endl;
    std::cout << "3.) Search by City" << std::endl;
    std::cout << "4.) Exit" << std::endl;
    choose_option(stats, house_manager);
}
void Menu::choose_option(HouseStatistics &stats, HouseManager &house_manager) {
    int user_option;
    while (true) {
        std::cout << "Type the Number of an Option Here: ";

        // Check if user input is valid
        if (!(std::cin >> user_option)) {
            std::cout << "\nInvalid Input. Please Enter a Number (1-3)." << std::endl;
            std::cin.clear();
            continue;
        }
        switch (user_option) {
            case 1:
                std::cout << "-----------------------" << std::endl;
                std::cout << "   GENERAL STAT INFO   " << std::endl;
                std::cout << "-----------------------" << std::endl;
                // Call House Statistics display method
                stats.print_stat_info();
                print_menu(stats, house_manager);
                break;
            case 2: {
                std::cout << "------------------------" << std::endl;
                std::cout << "    HOUSES IN BUDGET    " << std::endl;
                std::cout << "------------------------" << std::endl;

                // Get user budget minimum and maximum through console input
                int budget_min;
                int budget_max;
                while (true) {
                    std::cout << "Enter the minimum and maximum price for your budget." << std::endl;
                    std::cout << "Your values must be an integer n, with 50,000 < n < 20,000,000." << std::endl;
                    std::cout << "NOTE: Your maximum and minimum must have a difference > 0." << std::endl;
                    std::cout << "Enter your minimum value here: ";
                    std::cin >> budget_min;
                    if (!(budget_min) || budget_min < 50000 || budget_min > 20000000) {
                        std::cout << "Please enter a valid integer in the range 50,000 < n < 20,000,000" << std::endl;
                        std::cin.clear();
                        continue;
                    }
                    std::cout << "Enter your maximum value here: ";
                    std::cin >> budget_max;
                    if (!(budget_max) || budget_max < 50000 || budget_max > 20000000 || budget_max < budget_min) {
                        std::cout << "Please enter a valid integer in the range 49,999 < n < 20,000,001" << std::endl;
                        std::cin.clear();
                        continue;
                    }
                    break;
                }
                char y_or_no_choice;
                int start = 0;
                int max = 10;
                std::cout << "Now Printing the First 10 Houses in your Budget!" << std::endl << std::endl;
                while (true) {
                    start += 10;
                    // Call House Manager search by budget method to create vector
                    std::vector<House> houses_in_budget = house_manager.get_houses_in_budget(budget_min, budget_max);
                    // Call House Manager print houses method
                    house_manager.print_houses(houses_in_budget, start, max);

                    std::cout << std::endl << "Would you Like to Print the Next 10 Houses in your Budget? (If they Exist)" << std::endl;
                    std::cout << "Y or N: ";
                    while (true) {
                        std::cin.clear();
                        std::cin >> y_or_no_choice;
                        if ((y_or_no_choice != 'Y') && (y_or_no_choice != 'N') &&
                            (y_or_no_choice != 'y') && (y_or_no_choice != 'n')) {
                            std::cout << "Invalid Input. Please Enter Y or N: ";
                            continue;
                            }
                        break;
                    }
                    if (y_or_no_choice == 'Y' || y_or_no_choice == 'y') {
                        // print next 10 houses
                        start += 10;
                        continue;
                    }
                    break;
                }
                print_menu(stats, house_manager);
            }
            case 3: {
                // 1. Clear the newline left over from choosing '3' in the menu
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "------------------------" << std::endl;
                std::cout << "     HOUSES IN CITY     " << std::endl;
                std::cout << "------------------------" << std::endl;
                // Get user city and state through console input
                std::string city;
                std::string state;
                std::cout << "Enter a city and state from the United States." << std::endl;
                while (true) {
                    std::cout << "Enter the city here: ";
                    std::getline(std::cin, city);
                    bool found = false;
                    for (int i = 0; i < house_manager.get_num_of_houses(); i++) {
                        if (city == house_manager.get_houses_vector()[i].get_city()) {
                            std::cin.clear();
                            found = true;
                            break;
                        }
                    }
                    if (!(found)) {
                        continue;
                    }
                    found = false;
                    std::cout << "Enter the state here: ";
                    std::cin >> state;
                    for (int i = 0; i < house_manager.get_num_of_houses(); i++) {
                        if (state == house_manager.get_houses_vector()[i].get_state()) {
                            std::cin.clear();
                            found = true;
                            break;
                        }
                    }
                    if (!(found)) {
                        continue;
                    }
                    break;
                }

                char y_or_no_choice;
                int start = 0;
                int max = 10;
                std::cout << "Now Printing the First 10 Houses from your city!" << std::endl << std::endl;
                // Call HouseManager search by city method to create vector
                std::vector<House> houses_in_city = house_manager.get_houses_in_city(city, state);
                while (true) {
                    // Call House Manager print houses method
                    house_manager.print_houses(houses_in_city, start, max);

                    std::cout << std::endl << "Would you Like to Print the Next 10 Houses in the city provided? (If they Exist)" << std::endl;
                    std::cout << "Y or N: ";
                    while (true) {
                        std::cin.clear();
                        std::cin >> y_or_no_choice;
                        if ((y_or_no_choice != 'Y') && (y_or_no_choice != 'N') &&
                            (y_or_no_choice != 'y') && (y_or_no_choice != 'n')) {
                            std::cout << "Invalid Input. Please Enter Y or N: ";
                            continue;
                            }
                        break;
                    }
                    if (y_or_no_choice == 'Y' || y_or_no_choice == 'y') {
                        // print next 10 houses
                        start += 10;
                        continue;
                    }
                    break;
                }
                print_menu(stats, house_manager);
            }
            case 4:
                // Exit Program
                std::cout << "Exiting Program." << std::endl;
                break;
            default:
                std::cout << "Choice out of Range. Try Again with a Number (1-4)." << std::endl;
        }
        break;
    }
}