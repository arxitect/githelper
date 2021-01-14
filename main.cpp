#include <QtWidgets>
#include "app/MainWindow.h"
#include "app/Config.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    App::MainWindow mainWindow;

    auto config = App::Config::getInstance();
    config->loadStyles();

    mainWindow.show();
    return app.exec();
}