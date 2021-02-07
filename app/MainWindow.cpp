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
    copyBtn->setVisible(false);

    // Third level items
    noteLbl = new QLabel("");

    noteDisplay = new QLabel("");
    noteDisplay->setVisible(false);
    noteDisplay->setObjectName("noteDisplay");

    commandsLbl = new QLabel("I want to: ");
    // Init command 3 lvl Buttons
    commandBtn = new CommandButton("...");

    commandBtn->childButton = new CommandButton("...");
    commandBtn->childButton->setVisible(false);

    commandBtn->childButton->childButton = new CommandButton("...");
    commandBtn->childButton->childButton->setVisible(false);

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
    // Dark mode
    connect(darkModeBtn, SIGNAL(clicked()), SLOT(slotDarkModeBtnClicked()));
    // Copy button
    connect(copyBtn, SIGNAL(clicked()), SLOT(slotCopyBtnClicked()));
    // Slots for command button
    auto commandMenu = new QMenu(commandBtn);
    auto mainCommands = DbProxy::getMainCommands();
    for(const auto &command : mainCommands) {
        commandMenu->addAction(command.name, [&, command]() { slotCommandBtnClicked(command, commandBtn); });
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
    tSubLayoutL->addWidget(commandBtn->childButton);
    tSubLayoutL->addWidget(commandBtn->childButton->childButton);
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

void MainWindow::slotCopyBtnClicked() const {
    auto clipboard = QApplication::clipboard();
    clipboard->setText(usageDisplay->text().replace('\n', ' '));
}

void MainWindow::slotCommandBtnClicked(const Command &command, CommandButton *commandButton) const {
    // If has usage show copy button
    if(command.usage.length() > 0) copyBtn->setVisible(true);
    else copyBtn->setVisible(false);

    // collapse all children buttons
    if(commandButton->childButton != nullptr) {
        commandButton->childButton->setVisible(false);
        commandButton->childButton->setText("...");

        if(commandButton->childButton->childButton != nullptr) {
            commandButton->childButton->childButton->setVisible(false);
            commandButton->childButton->childButton->setText("...");
        }
    }

    // load usage text
    commandButton->setText(command.name);
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
    if(commandButton->childButton != nullptr && command.hasChild) {
        commandButton->childButton->setVisible(true);

        auto commandMenu = new QMenu(commandBtn);
        auto childCommands = DbProxy::getChildCommands(command.id);
        for (const auto &childCommand : childCommands) {
            commandMenu->addAction(childCommand.name,
                                   [=]() { slotCommandBtnClicked(childCommand, commandButton->childButton); });
        }
        commandButton->childButton->setMenu(commandMenu);
    }
}