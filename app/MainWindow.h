#ifndef GIT_HELPER_MAINWINDOW_H
#define GIT_HELPER_MAINWINDOW_H

#include <QtWidgets>

namespace App {

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QLabel *sloganPlbl;
    QLabel *usagePlbl;
    QLabel *notePlbl;
    QLabel *instructionsPlbl;

    void buildWindow();

public:
    explicit MainWindow(QWidget *pwgt = nullptr);
};

}

#endif //GIT_HELPER_MAINWINDOW_H
