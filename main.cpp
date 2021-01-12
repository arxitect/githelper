#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    /*TODO подключить стили,
     * вынести классы в неймспейс и создать синглтон для конфигов*/
    mainWindow.show();
    return app.exec();
}