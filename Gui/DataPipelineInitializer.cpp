#include "DataPipelineInitializer.h"

#include "Pipeline/DataPipeline.h"
#include "HouseObjects/HouseManager.h"
#include "HouseObjects/HouseStatistics.h"

#include <QDir>

DataPipelineInitializer::DataPipelineInitializer(HouseManager *houseManager, HouseStatistics *statistics,
                                                 QObject *parent)
    : QObject(parent), hm_(houseManager), stats_(statistics) {}

void DataPipelineInitializer::runPipeline(const QString &projectRoot) {
    // Get the path to the CSV and JSON files.
    QDir root(projectRoot);
    const QString csvPath = root.filePath(QStringLiteral("data/realtor_data.csv"));
    const QString jsonPath = root.filePath(QStringLiteral("data/clean_house_data.json"));

    // Convert the paths to a string.
    std::string err;
    const std::string csvStd = csvPath.toStdString();
    const std::string jsonStd = jsonPath.toStdString();

    // Lambda function to emit the progress signal. NOTE: Gemini helped me with this, as well as
    // The code below it.
    const auto onProgress = [this](int step, const std::string &msg) {
        emit progress(step, QString::fromStdString(msg));
    };

    // Run the data pipeline.
    if (!DataPipeline::run(*hm_, *stats_, csvStd, jsonStd, err, onProgress)) {
        emit cppPipelineFailed(QString::fromStdString(err));
        return;
    }

    // Emit the finished signal after the pipeline is finished.
    // This is used to signify that the pipeline is finished and the main window can be shown.
    emit progress(5, QStringLiteral("Ready."));
    emit cppPipelineFinished();
}
