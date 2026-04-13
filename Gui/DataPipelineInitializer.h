#ifndef M1OEP_DATAPIPELINEINITIALIZER_H
#define M1OEP_DATAPIPELINEINITIALIZER_H

#include <QObject>
#include <QString>

class HouseManager;
class HouseStatistics;

// QObject that runs DataPipeline::run on during the main window startup.
// Gives the progress for the loading bar UI.
class DataPipelineInitializer : public QObject {
    Q_OBJECT

public:
    // Constructor for the DataPipelineInitializer class.
    // explicit because we are passing pointers to the HouseManager and HouseStatistics classes.
    explicit DataPipelineInitializer(HouseManager *houseManager, HouseStatistics *statistics,
                                     QObject *parent = nullptr);

public slots:
    // Slot to run the data pipeline.
    void runPipeline(const QString &projectRoot);

signals:
    // Signals to emit the progress, failed, and finished signals.
    void progress(int step, const QString &message);
    void cppPipelineFailed(const QString &error);
    void cppPipelineFinished();

private:
    HouseManager *hm_;
    HouseStatistics *stats_;
};

#endif // M1OEP_DATAPIPELINEINITIALIZER_H
