#include "MainWindow.h"

using namespace App;

MainWindow::MainWindow(QWidget *pwgt) : QWidget(pwgt) {
    /* first, init elements of window */
    spaceForTop = new QSpacerItem(100, 20);
    sloganLbl = new QLabel("Find the git commands you need \n without digging through the web.");
    sloganLbl->setAlignment(Qt::AlignTop);
    usageLbl = new QLabel("Usage:");

    usageDisplay = new QLabel("git add <file.ext> "); /* this example text TODO: remove text*/
    usageDisplay->setObjectName("usageDisplay");

    copyBtn = new QPushButton();
    copyBtn->setObjectName("copyButton");
    copyBtn->setParent(usageDisplay);

    noteLbl = new QLabel("Note:");
    noteDisplay = new QLabel("To add all the files in the current directory "); /* this example text TODO: remove text*/
    noteDisplay->setObjectName("noteDisplay");
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
    auto fLvlLayout = new QHBoxLayout;

    auto sLvlLayout = new QHBoxLayout;
    auto sSubLayout = new QVBoxLayout;

    auto tLvlLayout = new QHBoxLayout;
    auto tSubLayoutL = new QVBoxLayout;
    auto tSubLayoutR = new QVBoxLayout;

    /* add widgets to layouts */

    // 1.
    fLvlLayout->addWidget(darkModeBtn);
    fLvlLayout->addSpacerItem(spaceForTop);
    fLvlLayout->addWidget(switchLangBtn);

    // 2.
    sSubLayout->addWidget(usageLbl);
    sSubLayout->addWidget(usageDisplay);
    sSubLayout->setAlignment(Qt::AlignTop);
    sLvlLayout->setContentsMargins(0, 10, 0, 0);
    sLvlLayout->addWidget(sloganLbl);
    sLvlLayout->addLayout(sSubLayout);
    // 3.
    tSubLayoutL->addWidget(commandsLbl);
    tSubLayoutL->addWidget(commandBtn);
    /* example buttons for command usage TODO remove it*/
    auto exCommandBtn = new  QPushButton("new changes");
    tSubLayoutL->addWidget(exCommandBtn);
    /* ---------------------------- */
    tSubLayoutL->setAlignment(Qt::AlignTop);
    tSubLayoutR->addWidget(noteLbl);
    tSubLayoutR->addWidget(noteDisplay);
    tSubLayoutR->setAlignment(Qt::AlignTop);
    tLvlLayout->addLayout(tSubLayoutL);
    tLvlLayout->addLayout(tSubLayoutR);

    // main
    mainLayout->addLayout(fLvlLayout);
    mainLayout->addLayout(sLvlLayout);
    mainLayout->addLayout(tLvlLayout);

    /* Set window config */
    setLayout(mainLayout);
    setObjectName("mainWindow");
    setWindowTitle("Git Helper");
    setFixedSize(510, 257);
}
