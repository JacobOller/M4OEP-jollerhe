#include "MainWindow.h"
#include "AppPaths.h"
#include "DataPipelineInitializer.h"
#include "ui_HouseDetailForm.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>

#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Real estate (CS2300)");
    resize(900, 640);

    // Create the central widget. This is the main widget that will contain all of the other widgets.
    auto *central = new QWidget(this);
    setCentralWidget(central);
    // Create an outer box layout that vertically stacks widgets within it. This is inside of the central widget.
    auto *outer = new QVBoxLayout(central);

    // Create a stacked widget. This holds the different pages of the UI, and we can switch between
    // these pages without having to create a new window for each page.
    pageStack = new QStackedWidget(central);
    outer->addWidget(pageStack);

    // Add the different pages to the stacked widget.
    pageStack->addWidget(buildLoadingPage());
    pageStack->addWidget(buildSearchPage());
    pageStack->addWidget(buildResultsPage());

    // Set the initial page to the loading page.
    pageStack->setCurrentIndex(PageLoading);

    // Start the startup pipeline (data loading, sorting, etc...)
    QTimer::singleShot(0, this, &MainWindow::beginStartupPipeline);
}

QWidget *MainWindow::buildLoadingPage() {
    auto *w = new QWidget;
    // Create a box layout that vertically stacks widgets within it. This is inside of the loading page widget.
    auto *layout = new QVBoxLayout(w);
    layout->addStretch();
    // <h2> is header 2, which controls the size of the text.
    auto *title = new QLabel("<h2>Loading...</h2>");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    // Create a label that displays the status of the startup pipeline.
    loadStatusLabel = new QLabel("Starting up");
    loadStatusLabel->setAlignment(Qt::AlignCenter);
    loadStatusLabel->setWordWrap(true);
    // Add this new label to the layout.
    layout->addWidget(loadStatusLabel);
    // Create a progress bar that displays the progress of the startup pipeline.
    loadProgress = new QProgressBar;
    // there are 5 steps, so set the range to 0-5.
    loadProgress->setRange(0, 5);
    loadProgress->setValue(0);
    // Add this new progress bar to the layout.
    layout->addWidget(loadProgress);
    // Add a stretch to the layout. This is used to push the widgets to the top and bottom of the layout.
    layout->addStretch();
    return w;
}

QWidget *MainWindow::buildSearchPage() {
    auto *w = new QWidget;

    // Sets up the search page UI. I designed this UI in Qt Creator, then exported it to a .ui file.
    // This made it easier to format the UI in a consistent way.
    uiSearch.setupUi(w);

    // Connect the textChanged signal of each line edit to updateSearchButtonEnabled.
    // This is used to disable the search button until one or more search fields is filled.
    // The search button is refreshed whenever the text in any of the line edits is changed.
    // NOTE I would not have known to use the lambda function here if it weren't for Gemini.
    const auto refresh = [this]() { updateSearchButtonEnabled(); };
    connect(uiSearch.lineEditZip, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });
    connect(uiSearch.lineEditCity, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });
    connect(uiSearch.lineEditState, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });
    connect(uiSearch.lineEditBeds, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });
    connect(uiSearch.lineEditBaths, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });
    connect(uiSearch.lineEditSqft, &QLineEdit::textChanged, this,
            [refresh](const QString &) { refresh(); });

    // Disable the button until one or more search fields is filled.
    uiSearch.pushButton->setEnabled(false);
    // Connect the button to the search method.
    // The first this is the parent, which is just the main window, and [this] is a lambda function, where
    // [this] acts as a pointer to the main window's private variables, () are empty parameters, and {} is the body of the function.
    // The function just gets the text from the search fields and passes it to the HouseManager's filter_by_search method.
    connect(uiSearch.pushButton, &QPushButton::clicked, this, [this]() {
        const std::string zip = uiSearch.lineEditZip->text().toStdString();
        const std::string city = uiSearch.lineEditCity->text().toStdString();
        const std::string state = uiSearch.lineEditState->text().toStdString();
        const std::string beds = uiSearch.lineEditBeds->text().toStdString();
        const std::string baths = uiSearch.lineEditBaths->text().toStdString();
        const std::string size = uiSearch.lineEditSqft->text().toStdString();
        if (!hm.filter_by_search(zip, city, state, beds, baths, size)) {
            QMessageBox::warning(this, "Search",
                 "Need at least one field, and beds/baths/size must be valid integers if you fill them in.");
            return;
        }
        // Get the matches from the HouseManager method.
        const auto& matches = hm.get_houses_search_ref();
        if (matches.empty()) {
            // If no matches are found, show a message box to the user that says nothing matched.
            QMessageBox::information(this, "Search", "Nothing matched.");
            return;
        }
        // Show the results to the user.
        showHouseResults(matches, "Results");
    });
    // Connect the exit button to the quit application method.
    connect(uiSearch.pushButtonExit, &QPushButton::clicked, qApp, &QApplication::quit);

    // Refresh the search button to see if it should be enabled.
    updateSearchButtonEnabled();
    return w;
}

void MainWindow::updateSearchButtonEnabled() {
    // Check if any of the search fields are filled.
    // NOTE: Gemini helped me a lot with the following 7 lines of code.
    const bool any = !uiSearch.lineEditZip->text().trimmed().isEmpty() ||
            !uiSearch.lineEditCity->text().trimmed().isEmpty() ||
            !uiSearch.lineEditState->text().trimmed().isEmpty() ||
            !uiSearch.lineEditBeds->text().trimmed().isEmpty() ||
            !uiSearch.lineEditBaths->text().trimmed().isEmpty() ||
            !uiSearch.lineEditSqft->text().trimmed().isEmpty();
    // If there is any text in the search fields, enable the search button.
    uiSearch.pushButton->setEnabled(any);
}

QWidget *MainWindow::buildResultsPage() {
    auto *w = new QWidget;
    auto *layout = new QVBoxLayout(w);
    resultsHeader = new QLabel;
    layout->addWidget(resultsHeader);
    // Create a label for the number of results that are being shown.
    resultsCapLabel = new QLabel;
    // Set the word wrap to true so that the label can wrap to next line instead of messing upthe window.
    resultsCapLabel->setWordWrap(true);
    layout->addWidget(resultsCapLabel);
    // Create a tab widget for the results. This is where each individual house object will be displayed,
    // and the user will be able to click on each individual tab to see the details of that house.
    resultsTabs = new QTabWidget;
    layout->addWidget(resultsTabs, 1);
    // Create a button that when clicked will go back to the search page to allow the user to search again. 
    auto *back = new QPushButton("Back");
    // The action that brings the user back to the search page.
    connect(back, &QPushButton::clicked, this, &MainWindow::goToSearchPage);
    layout->addWidget(back);
    return w;
}

QWidget *MainWindow::createHouseDetailWidget(const House &house) {
    auto *w = new QWidget;
    // Sets up the house detail UI. I designed this UI in Qt Creator, then exported it to a .ui file.
    // This made it easier to format the UI in a consistent way.
    Ui::HouseDetailForm ui;
    ui.setupUi(w);
    // Set the text of each label to the corresponding value of the house object's attribute.
    ui.valueRealtor->setText(QString::fromStdString(house.get_brokered_by()));
    ui.valueStatus->setText(QString::fromStdString(house.get_status()));
    ui.valuePrice->setText(QString::number(house.get_price()));
    ui.valueBeds->setText(QString::number(house.get_beds()));
    ui.valueBaths->setText(QString::number(house.get_baths()));
    ui.valueAcres->setText(QString::number(house.get_size_in_acres(), 'f', 2));
    ui.valueStreetId->setText(QString::fromStdString(house.get_street_id()));
    ui.valueCity->setText(QString::fromStdString(house.get_city()));
    ui.valueState->setText(QString::fromStdString(house.get_state()));
    ui.valueZipCode->setText(QString::fromStdString(house.get_zip_code()));
    ui.valueSize->setText(QString::number(house.get_house_size()));
    ui.valuePrevSold->setText(QString::fromStdString(house.get_prev_sold_date()));
    return w;
}

void MainWindow::showHouseResults(const std::vector<House> &houses, const QString &headerText) {
    resultsHeader->setText(headerText);
    // Clear the results tabs to avoid duplicates.
    resultsTabs->clear();

    const long total = houses.size();
    const long shown = std::min(total, static_cast<long>(maxResultTabs));
    // If there are more results than the max, show the number of results that are being shown out of the max.
    if (total > shown) {
        // Use StringLiterals because it is standard for Qt to use them when concatinating like this.
        resultsCapLabel->setText(QStringLiteral("Only showing ") + QString::number(shown) +
                QStringLiteral(" of ") + QString::number(total) +
                QStringLiteral(" (cap is ") + QString::number(maxResultTabs));
    } else {
        resultsCapLabel->setText(QString::number(total) + QStringLiteral(" matches."));
    }
    // Add each house object to the results tabs.
    for (long i = 0; i < shown; ++i) {
        const House& h = houses[i];
        const QString tabTitle = QStringLiteral("#") + QString::number(i + 1) + QStringLiteral(" - $") +
                QString::number(h.get_price());
        resultsTabs->addTab(createHouseDetailWidget(h), tabTitle);
    }
    // Set the current page to the results page.
    pageStack->setCurrentIndex(PageResults);
}

void MainWindow::goToSearchPage() {
    // Set the current page to the search page.
    // This is called when the user clicks the back button in the results page.
    pageStack->setCurrentIndex(PageSearch);
}

void MainWindow::beginStartupPipeline() {
    const QString root = AppPaths::projectRoot();
    // Create a new thread for the loading screen. That way the loading screen can run while the other processes are happening.
    loadThread = new QThread(this);
    
    // Create a new data pipeline initializer, which will handle the loading of the data seperately from the loading screen.
    auto *initializer = new DataPipelineInitializer(&hm, &stats);
    // Move the initializer to the loading thread.
    initializer->moveToThread(loadThread);

    // Connect the initializer to the loading screen to display the progress.
    // NOTE: Gemini helped me a lot with the following 15 lines of code.
    connect(initializer, &DataPipelineInitializer::progress, this, &MainWindow::showLoadProgress,
            Qt::QueuedConnection);
    connect(initializer, &DataPipelineInitializer::cppPipelineFailed, this,
            &MainWindow::cppPipelineFailed, Qt::QueuedConnection);
    connect(initializer, &DataPipelineInitializer::cppPipelineFinished, this,
            &MainWindow::cppPipelineFinished, Qt::QueuedConnection);

    connect(loadThread, &QThread::started, initializer, [initializer, root]() {
        initializer->runPipeline(root);
    });

    connect(loadThread, &QThread::finished, initializer, &QObject::deleteLater);

    loadThread->start();
}

void MainWindow::showLoadProgress(int step, const QString &message) {
    // Set the text of the loading status label to the current task.
    loadStatusLabel->setText(message);
    // Set the progress percentage.
    loadProgress->setValue(std::clamp(step, 0, 5));
}

void MainWindow::cppPipelineFailed(const QString &error) {
    loadThread->quit();
    loadThread->wait();
    QMessageBox::critical(this, "The startup pipeline failed. Quitting the application.", error);
    QApplication::quit();
}

void MainWindow::cppPipelineFinished() {
    loadThread->quit();
    loadThread->wait();
    goToSearchPage();
}
