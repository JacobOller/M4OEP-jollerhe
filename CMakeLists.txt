cmake_minimum_required(VERSION 3.8)
project(M1OEP)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        HouseObjects/House.h
        HouseObjects/House.cpp
        data/realtor_data.csv
        HouseObjects/HouseManager.h
        HouseObjects/HouseManager.cpp
        HouseObjects/HouseStatistics.h
        HouseObjects/HouseStatistics.cpp
        Sorting/HeapSort.h
        Sorting/HeapSort.cpp
        Menu/Menu.h
        Menu/Menu.cpp)
add_executable(test testing.cpp
        HouseObjects/House.h
        HouseObjects/House.cpp
        data/realtor_data.csv
        HouseObjects/HouseManager.h
        HouseObjects/HouseManager.cpp
        HouseObjects/HouseStatistics.h
        HouseObjects/HouseStatistics.cpp
        Sorting/HeapSort.h
        Sorting/HeapSort.cpp
        Menu/Menu.h
        Menu/Menu.cpp)
