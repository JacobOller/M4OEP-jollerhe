#include "Pipeline/DataPipeline.h"
#include "HouseObjects/HouseManager.h"
#include "HouseObjects/HouseStatistics.h"
#include "Sorting/HeapSort.h"

namespace DataPipeline {

bool run(HouseManager &hm, HouseStatistics &stats, const std::string &csvPath,
         const std::string &jsonOutPath, std::string &err,
         std::function<void(int step, const std::string &message)> progress) {
    // The progress function is used to display the progress of the pipeline to the user.
    if (progress) {
        progress(1, "Reading the CSV...");
    }
    // Load the data from the CSV file.
    if (!hm.data_from_file(csvPath)) {
        err = "Could not load data file: " + csvPath;
        return false;
    }

    if (progress) {
        progress(2, "Heap sort by price...");
    }
    unsigned long reads = 0;
    unsigned long allocations = 0;
    HeapSort::heapSort(hm.get_houses_vector(), reads, allocations);

    if (progress) {
        progress(3, "Calculating statistics...");
    }
    stats.calculate_mean_values(hm);
    stats.calculate_max_values(hm);
    stats.calculate_broker_values(hm);
    const int threshold = 20;
    stats.calculate_valid_zipcodes(hm.get_houses_vector(), threshold);
    stats.calculate_city_values(hm.get_houses_vector());

    if (progress) {
        progress(4, "Writing JSON...");
    }
    hm.export_data(jsonOutPath);
    return true;
}

} // namespace DataPipeline
