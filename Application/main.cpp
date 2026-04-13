#include "Gui/MainWindow.h"

#include <QApplication>

// Main function: create the application and window.
// Note: must include command line arguments as parameters for QApplication, even though I don't need them.
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
