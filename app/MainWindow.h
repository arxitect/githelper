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
#include "helpers/Config.h"
#include "helpers/DbProxy.h"
#include "parts/CommandButton.h"

namespace App {

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QLabel* sloganLbl;
    QLabel* usageLbl;
    QLabel* noteLbl;
    QLabel* commandsLbl;
    QRadioButton* darkModeBtn;
    QSpacerItem* spaceForTop;
    QLabel* usageDisplay;
    CommandButton* commandBtn;
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
private slots:
    void slotDarkModeBtnClicked() const;
    void slotCommandBtnClicked(const Command &command, CommandButton *commandButton) const;
    void slotCopyBtnClicked() const;
};

}

#endif //GIT_HELPER_MAINWINDOW_H
