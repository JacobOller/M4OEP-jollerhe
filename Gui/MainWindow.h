#ifndef M1OEP_MAINWINDOW_H
#define M1OEP_MAINWINDOW_H

#include "../HouseObjects/HouseManager.h"
#include "../HouseObjects/HouseStatistics.h"
#include "ui_SearchForm.h"

#include <QMainWindow>
#include <QString>
#include <vector>

// Declare these classes here so that they are compiled before the MainWindow class is.
class QLabel;
class QProgressBar;
class QPushButton;
class QStackedWidget;
class QTabWidget;
class QThread;

// MainWindow class, which is the only window used for this UI.
class MainWindow : public QMainWindow {
    // Q_OBJECT is a qt macro that is used to allow the use of signals and slots in the class.
    Q_OBJECT

public:
    // Constructor for the MainWindow class. This is where all of the widgets will be presented.
    explicit MainWindow(QWidget *parent = nullptr);

// Private slots are used to handle the triggers throughout the program.
private slots:
    // The method for displaying the progress of the loading screen.
    void showLoadProgress(int step, const QString &message);
    // Called if the C++ startup pipeline fails because of an error. Shows the error and quits.
    void cppPipelineFailed(const QString &error);
    // Called when the C++ startup pipeline finishes successfully. This means that:
    // the data was loaded and sorted, the stats methods completed, and the json file exported).
    void cppPipelineFinished();

private:
    // Starts the C++ pipeline on a different thread, this allows for the loading bar
    // to display whats going on while the background processes are happening.
    // The processes are: load CSV, heap-sort, compute statistics, export JSON
    // (see DataPipeline / DataPipelineInitializer).
    void beginStartupPipeline();
    // The method for navigating to the search page.
    void goToSearchPage();
    // The method for displaying the house results. Used within the buildResultsPage method.
    void showHouseResults(const std::vector<House> &houses, const QString &headerText);

    // The method for building the loading page.
    QWidget *buildLoadingPage();
    // The method for building the search page.
    QWidget *buildSearchPage();
    // The method for building the results page.
    QWidget *buildResultsPage();
    // The method for creating the house detail widget (used in the results page).
    QWidget *createHouseDetailWidget(const House &house);
    // Allows the user to press the button when at least one search field is filled.
    void updateSearchButtonEnabled();

    // Only display a max of 200 results, if there are more than that then the search is too general.
    static constexpr int maxResultTabs = 200;

    // The different pages of the UI.
    enum Page { PageLoading = 0, PageSearch = 1, PageResults = 2 };

    // The house manager and statistics objects.
    HouseManager hm;
    HouseStatistics stats;

    // The stacked widget that holds the different pages of the UI.
    QStackedWidget *pageStack = nullptr;
    // The label for displaying the status for the loading screen (%).
    QLabel *loadStatusLabel = nullptr;
    // The progress bar for the loading screen.
    QProgressBar *loadProgress = nullptr;

    // Search form from SearchForm.ui (line edits + Get Results / Exit), applied in buildSearchPage().
    Ui::SearchForm uiSearch;

    // The tab widget for the results page (top of the page that shows different house objects).
    QTabWidget *resultsTabs = nullptr;
    // The label for displaying the header of the results page.
    QLabel *resultsHeader = nullptr;
    // The label for displaying the number of results that are being shown.
    QLabel *resultsCapLabel = nullptr;
    // The thread for the loading screen.
    QThread *loadThread = nullptr;
};

#endif // M1OEP_MAINWINDOW_H
