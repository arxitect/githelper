#include <QApplication>
#include "app/MainWindow.h"
#include "app/helpers/Config.h"

using namespace App;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    auto config = Config::getInstance();
    app.setWindowIcon(QIcon(config->getRootPath() + "/assets/images/icons/app.png"));

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}