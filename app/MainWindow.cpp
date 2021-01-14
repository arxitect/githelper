#include "MainWindow.h"

using namespace App;

MainWindow::MainWindow(QWidget *pwgt) : QWidget(pwgt) {
    /* first, init elements of window */
    spaceForTop = new QSpacerItem(40, 20);
    sloganLbl = new QLabel("Find the git commands you need \n without digging through the web.");
    usageLbl = new QLabel("Usage:");
    usageDisplay = new QLabel("git add <file.ext> "); /* this example text TODO: remove text*/
    noteLbl = new QLabel("Note:");
    noteDisplay = new QLabel("To add all the files in the current directory "); /* this example text TODO: remove text*/
    commandsLbl = new QLabel("I want to: ");
    darkModeBtn = new QRadioButton("&Dark mode");

    /* this example items TODO init by setting*/
    switchLangBtn = new QPushButton("Ru");
    auto langMenu = new QMenu(switchLangBtn);
    langMenu->addAction("En");
    switchLangBtn->setMenu(langMenu);
    switchLangBtn->setObjectName("langButton");

    commandBtn = new QPushButton("...");
    auto commandMenu = new QMenu(commandBtn);
    /* this example items TODO init by data from database*/
    commandMenu->addAction("add");
    commandMenu->addAction("cherry-pick");
    commandMenu->addAction("clone");
    commandBtn->setMenu(commandMenu);

    buildWindow();
}

void MainWindow::buildWindow() {
    /* init layouts */
    auto mainLayout = new QVBoxLayout;
    auto firstLvlLayout = new QHBoxLayout;

    auto secondLvlLayout = new QHBoxLayout;
    auto secondSubLayout = new QVBoxLayout;

    auto thirdLvlLayout = new QHBoxLayout;
    auto thirdSubLayoutL = new QVBoxLayout;
    auto thirdSubLayoutR = new QVBoxLayout;

    /* add widgets to layouts */

    // 1.
    firstLvlLayout->addWidget(darkModeBtn);
    firstLvlLayout->addSpacerItem(spaceForTop);
    firstLvlLayout->addWidget(switchLangBtn);

    // 2.
    secondSubLayout->addWidget(usageLbl);
    secondSubLayout->addWidget(usageDisplay);
    secondLvlLayout->addWidget(sloganLbl);
    secondLvlLayout->addLayout(secondSubLayout);

    // 3.
    thirdSubLayoutL->addWidget(commandsLbl);
    thirdSubLayoutL->addWidget(commandBtn);
    /* example buttons for command usage TODO remove it*/
    auto exCommandBtn = new  QPushButton("new changes");
    thirdSubLayoutL->addWidget(exCommandBtn);
    /* ---------------------------- */
    thirdSubLayoutR->addWidget(noteLbl);
    thirdSubLayoutR->addWidget(noteDisplay);
    thirdLvlLayout->addLayout(thirdSubLayoutL);
    thirdLvlLayout->addLayout(thirdSubLayoutR);

    // main
    mainLayout->addLayout(firstLvlLayout);
    mainLayout->addLayout(secondLvlLayout);
    mainLayout->addLayout(thirdLvlLayout);

    /* Set window config */
    setLayout(mainLayout);
    setObjectName("mainWindow");
    setWindowTitle("Git Helper");
    setFixedSize(510, 257);
}
