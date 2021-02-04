#include "Config.h"
#include <QApplication>
#include <QtCore/QFile>

using namespace App;

Config* Config::config = nullptr;

Config* Config::getInstance() {
    if(config == nullptr) {
        config = new Config;
    }

    return config;
}

/* loadSQLConnection: connect to db with commands (once for application, closing in destructor) */
void Config::loadSQLConnection() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("githelperdb");
    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("password");
    if (!db.open()) {

    }
}

/* loadStyles: loading app styles by mode */
void Config::loadStyles(bool darkMode) const {
    QString strCss;
    QString prefix = darkMode ? "dark" : "light";
    QStringList styles {
        "../assets/styles/" + prefix + "/app.qss",
        "../assets/styles/" + prefix + "/buttons.qss",
        "../assets/styles/" + prefix + "/labels.qss"
    };

    for (auto &filename : styles) {
        QFile file(filename);
        file.open(QFile::ReadOnly);

        strCss += QLatin1String(file.readAll());

        file.close();
    }

    qApp->setStyleSheet(strCss);
}

Config::~Config() {
    db.close();
}

