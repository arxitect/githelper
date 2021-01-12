#include "MainWindow.h"

MainWindow::MainWindow(QWidget *pwgt) : QWidget(pwgt) {
    sloganPlbl = new QLabel(QObject::tr("Find the git commands you need \n without digging through the web."));
    usagePlbl = new QLabel(QObject::tr("Usage:"));
    notePlbl = new QLabel(QObject::tr("Note:"));
    instructionsPlbl = new QLabel(QObject::tr("I want to: "));

    /*TODO Придумать как вынести слои более лаконично*/
    auto mainLayout = new QVBoxLayout;
    auto firstLvlLayout = new QHBoxLayout;

    auto secondLvlLayout = new QHBoxLayout;
    auto secondSubLayout = new QVBoxLayout;

    auto thirdLvlLayout = new QHBoxLayout;
    auto thirdSubLayoutL = new QVBoxLayout;
    auto thirdSubLayoutR = new QVBoxLayout;

    secondSubLayout->addWidget(usagePlbl);

    secondLvlLayout->addWidget(sloganPlbl);
    secondLvlLayout->addLayout(secondSubLayout);

    thirdSubLayoutL->addWidget(instructionsPlbl);
    thirdSubLayoutR->addWidget(notePlbl);
    thirdLvlLayout->addLayout(thirdSubLayoutL);
    thirdLvlLayout->addLayout(thirdSubLayoutR);

    mainLayout->setContentsMargins(10, 0, 10, 0);
    mainLayout->addLayout(firstLvlLayout);
    mainLayout->addLayout(secondLvlLayout);
    mainLayout->addLayout(thirdLvlLayout);

    setLayout(mainLayout);
}