#include <QtWidgets>
#include "app/MainWindow.h"
#include "app/Config.h"

using namespace App;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    auto config = Config::getInstance();
    config->loadStyles();

    mainWindow.show();
    return app.exec();
}