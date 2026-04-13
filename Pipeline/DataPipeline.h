//
// Shared CSV → sort → statistics → JSON export pipeline for console App and GUI worker.
//

#ifndef M1OEP_DATAPIPELINE_H
#define M1OEP_DATAPIPELINE_H

#include <functional>
#include <string>

class HouseManager;
class HouseStatistics;

namespace DataPipeline {

// Loads CSV, validates non-empty dataset, heap-sorts, computes statistics, exports JSON.
// On failure, sets error to a short message and returns false.
// If progress is set it is used to display the progress of tasks for steps 1–4 (load, sort, statistics, export).
bool run(HouseManager &hm, HouseStatistics &stats, const std::string &csvPath,
         const std::string &jsonOutPath, std::string &error,
         std::function<void(int step, const std::string &message)> progress = {});

} // namespace DataPipeline

#endif // M1OEP_DATAPIPELINE_H
