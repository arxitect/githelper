#ifndef GIT_HELPER_MAINWINDOW_H
#define GIT_HELPER_MAINWINDOW_H

#include <QtWidgets>

namespace App {

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QLabel* sloganLbl;
    QLabel* usageLbl;
    QLabel* noteLbl;
    QLabel* commandsLbl;
    QRadioButton* darkModeBtn;
    QPushButton* switchLangBtn;
    QSpacerItem* spaceForTop;
    QLabel* usageDisplay;
    QPushButton* commandBtn;
    QLabel* noteDisplay;
    QPushButton* copyBtn;

    void buildWindow();
public:
    explicit MainWindow(QWidget *pwgt = nullptr);
};

}

#endif //GIT_HELPER_MAINWINDOW_H
