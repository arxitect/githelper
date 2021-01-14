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

void Config::loadStyles() const {
    QString strCss;
    QStringList styles {
        "../assets/styles/app.qss",
        "../assets/styles/buttons.qss",
        "../assets/styles/labels.qss"
    };

    for (auto &filename : styles) {
        QFile file(filename);
        file.open(QFile::ReadOnly);

        strCss += QLatin1String(file.readAll());

        file.close();
    }

    qApp->setStyleSheet(strCss);
}


