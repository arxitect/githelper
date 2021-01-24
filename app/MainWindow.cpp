#include "MainWindow.h"

using namespace App;

auto config = Config::getInstance();
/* Init elements of MainWindow widget */
MainWindow::MainWindow(QWidget *pwgt) : QWidget(pwgt), settings("Git Helper", "Git Helper") {
    config->loadSQLConnection();
    // First level items
    spaceForTop = new QSpacerItem(100, 20);
    darkModeBtn = new QRadioButton("&Dark mode");

    // Second level items
    sloganLbl = new QLabel("Find the git commands you need \n without digging through the web.");
    sloganLbl->setAlignment(Qt::AlignTop);
    sloganLbl->setObjectName("sloganLbl");

    usageLbl = new QLabel("Usage:");

    usageDisplay = new QLabel("");
    usageDisplay->setObjectName("usageDisplay");

    copyBtn = new QPushButton();
    copyBtn->setObjectName("copyButton");
    copyBtn->setParent(usageDisplay);

    // Third level items
    noteLbl = new QLabel("");

    noteDisplay = new QLabel("");
    noteDisplay->setVisible(false);
    noteDisplay->setObjectName("noteDisplay");

    commandsLbl = new QLabel("I want to: ");

    commandBtn = new QPushButton("...");

    // hidden command buttons
    commandBtn2 = new QPushButton("...");
    commandBtn2->setVisible(false);
    commandBtn3 = new QPushButton("...");
    commandBtn3->setVisible(false);

    // logic of elements
    readSettings();
    connectElements();
    buildWindow();
}

/* Settings */
void MainWindow::readSettings() {
    settings.beginGroup("/Settings");

    // load Dark mode
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
    // darkMode
    connect(darkModeBtn, SIGNAL(clicked()), SLOT(slotDarkModeBtnClicked()));

    // generate slots for command button
    auto commandMenu = new QMenu(commandBtn);
    auto mainCommands = DbProxy::getMainCommands();
    for(auto &command : mainCommands) {
        commandMenu->addAction(command.name, [&, command](){ slotCommandButtonClicked(command); });
    }
    commandBtn->setMenu(commandMenu);
}

/* Build elements to MainWindow widget */
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
    tSubLayoutL->addWidget(commandBtn2);
    tSubLayoutL->addWidget(commandBtn3);
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

/* SLOTS */
void MainWindow::slotDarkModeBtnClicked() const {
    config->loadStyles(darkModeBtn->isChecked());
}

void MainWindow::slotCommandButtonClicked(const Command& command) const {

    // load usage text
    commandBtn->setText(command.name);
    usageDisplay->setText(command.usage);

    // if has note, load note text
    if(command.note.length() > 0) {
        noteLbl->setText("Note:");
        noteDisplay->setVisible(true);
        noteDisplay->setText(command.note);
    }else {
        noteLbl->setText("");
        noteDisplay->setVisible(false);
        noteDisplay->setText("");
    }

    // load child element of button
    if(command.hasChild) {
        commandBtn2->setVisible(true);

        auto commandMenu = new QMenu(commandBtn);
        auto childCommands = DbProxy::getChildCommands(command.id);
        for(auto &childCommand : childCommands) {
            commandMenu->addAction(childCommand.name);
        }
        commandBtn2->setMenu(commandMenu);
    }else {
        commandBtn2->setVisible(false);
    }
}