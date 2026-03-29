//
// Created by jacob on 2/1/2026.
//

#include "./HeapSort.h"
#include <vector>

// Helper function for heapSort
inline int HeapSort::leftChild(const int i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap

void HeapSort::percolateDown(std::vector<House> &items, int i, unsigned long& n, int& child, House& tmp, unsigned long& reads) {
    reads += 1;
    for(tmp = items[i]; leftChild(i) < n; i = child) { // This counts as 1 read
        child = leftChild(i);
        // choose the child with the larger value
        if (child != n - 1) {
            if (items[child] < items[child + 1]) { // This counts as 2 reads
                reads += 2;
                ++child;
            }
        }
        // if the parent is less than the child, swap them
        if (tmp < items[child]) { // This counts as 2 reads
            reads += 2;
            items[i] = items[child]; // This counts as 1 read
            reads += 1;
        } else { // This also counts as 2 reads
            reads += 2;
            // parent is >= both children. nothing more to do.
            break;
        }
    }
    items[i] = tmp;
}

std::vector<House> HeapSort::heapSort(std::vector<House> &items, unsigned long& reads, unsigned long& allocations) {
    reads = allocations = 0;
    int i, child; // This allocates 2 * sizeof(int)
    allocations += 2 * sizeof(int);
    House temp, tmp; // This allocates 2 * sizeof(House)
    allocations += 2 * sizeof(House);
    unsigned long j, n; // This allocates 2 * sizeof(unsigned long)
    allocations += 2 * sizeof(unsigned long);
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        n = items.size();
        percolateDown(items, i, n, child, tmp, reads);
    }

    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0]; // This counts as one read
        reads += 1;
        items[0] = items[j]; // This counts as one read
        reads += 1;
        items[j] = temp; // This counts as one read
        reads += 1;

        // make it into a heap again
        i = 0;
        percolateDown(items, i, j, child, tmp, reads);
    }
    return items;
}
