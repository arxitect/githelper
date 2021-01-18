/****************************************************************************
 *
 * This file is part of the Git Helper application.
 *
 * This class is the basis of the entire application.
 * Elements are created here, settings are saved, and
 * signals for elements are set.
 *
****************************************************************************/
#ifndef GIT_HELPER_MAINWINDOW_H
#define GIT_HELPER_MAINWINDOW_H

#include <QtWidgets>
#include "Config.h"
#include "DbProxy.h"

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
    QSettings settings;

    void connectElements();
    void buildWindow();
    void readSettings();
    void writeSettings();
public:
    explicit MainWindow(QWidget *pwgt = nullptr);
    ~MainWindow() override;
public slots:
    void slotDarkModeBtnClicked() const;
    void slotCommandButtonClicked(const Command& command) const;
};

}

#endif //GIT_HELPER_MAINWINDOW_H
