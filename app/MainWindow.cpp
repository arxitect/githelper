#include "MainWindow.h"

using namespace App;

auto config = Config::getInstance();
// Init elements of MainWindow widget
MainWindow::MainWindow(QWidget *pwgt) : QWidget(pwgt), settings("Git Helper", "Git Helper") {
    spaceForTop = new QSpacerItem(100, 20);
    sloganLbl = new QLabel("Find the git commands you need \n without digging through the web.");
    sloganLbl->setAlignment(Qt::AlignTop);
    sloganLbl->setObjectName("sloganLbl");

    usageLbl = new QLabel("Usage:");

    usageDisplay = new QLabel("git add <file.ext> "); /* this example text TODO: remove text*/
    usageDisplay->setObjectName("usageDisplay");

    copyBtn = new QPushButton();
    copyBtn->setObjectName("copyButton");
    copyBtn->setParent(usageDisplay);

    noteLbl = new QLabel("");

    noteDisplay = new QLabel("");
    noteDisplay->setVisible(false);
    noteDisplay->setObjectName("noteDisplay");

    commandsLbl = new QLabel("I want to: ");
    darkModeBtn = new QRadioButton("&Dark mode");

    commandBtn = new QPushButton("...");
    auto commandMenu = new QMenu(commandBtn);
    auto mainCommands = (new DbProxy())->getMainCommands();
    /** TODO command button usage*/
    for(auto &command : mainCommands) {
        commandMenu->addAction(command.name, this,SLOT(slotCommandButton()));
    }
    commandBtn->setMenu(commandMenu);

    readSettings();
    connectElements();
    buildWindow();
}

// Settings
void MainWindow::readSettings() {
    settings.beginGroup("/Settings");

    //Dark mode
    auto darkMode = settings.value("/darkMode", false).toBool();
    darkModeBtn->setChecked(darkMode);

    settings.endGroup();
}

void MainWindow::writeSettings() {
    settings.beginGroup("/Settings");

    settings.setValue("/darkMode", darkModeBtn->isChecked());

    settings.endGroup();
}

void MainWindow::connectElements() {
    connect(darkModeBtn, SIGNAL(clicked()), SLOT(slotDarkModeBtnClicked()));
}

// build all elements to MainWindow widget
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
    //fLvlLayout->addWidget(switchLangBtn);

    // 2.
    sSubLayout->setAlignment(Qt::AlignTop);
    sSubLayout->addWidget(usageLbl);
    sSubLayout->addWidget(usageDisplay);
    sLvlLayout->setContentsMargins(0, 10, 0, 0);
    sLvlLayout->addWidget(sloganLbl);
    sLvlLayout->addLayout(sSubLayout);
    // 3.
    tSubLayoutL->setAlignment(Qt::AlignTop);
    tSubLayoutL->setContentsMargins(0, 0, 30, 0);
    tSubLayoutL->addWidget(commandsLbl);
    tSubLayoutL->addWidget(commandBtn);
    tSubLayoutR->addWidget(noteLbl);
    tSubLayoutR->addWidget(noteDisplay);
    tSubLayoutR->setAlignment(Qt::AlignTop);
    tLvlLayout->setContentsMargins(0, 10, 0, 0);
    tLvlLayout->addLayout(tSubLayoutL);
    tLvlLayout->addLayout(tSubLayoutR);

    // main
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(fLvlLayout);
    mainLayout->addLayout(sLvlLayout);
    mainLayout->addLayout(tLvlLayout);

    /* Set window config */
    config->loadStyles(darkModeBtn->isChecked());

    setLayout(mainLayout);
    setObjectName("mainWindow");
    setWindowTitle("Git Helper");
    setFixedSize(510, 257);
}

MainWindow::~MainWindow() {
    writeSettings();
}

// SLOTS
void MainWindow::slotDarkModeBtnClicked() {
    config->loadStyles(darkModeBtn->isChecked());
}

void MainWindow::slotCommandButton() {
    qDebug() << "Click!!!!";
}