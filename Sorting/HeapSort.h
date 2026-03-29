//
// Created by jacob on 2/1/2026.
// I took this class from Project 4 of a UVM class that I took
// last semester "called Data Structures and Algorithms".
// The class HeapSort sorts the real estate data based on the price of the house.
//

#ifndef M1OEP_HEAPSORT_H
#define M1OEP_HEAPSORT_H

#include "../HouseObjects/House.h"
#include <vector>

class HeapSort {
public:
    // Helper function for heapSort
    static inline int leftChild(const int i);
    // Helper function for heapSort
    static void percolateDown(std::vector<House> &items, int i, unsigned long& n,
        int& child, House& tmp, unsigned long& reads);
    // Main method that uses both helper functions above to implement the heap sort algorithm
    static std::vector<House> heapSort(std::vector<House> &items, unsigned long& reads, unsigned long& allocations);
};

#endif //M1OEP_HEAPSORT_H