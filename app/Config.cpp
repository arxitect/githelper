#include "Config.h"
#include <QApplication>
#include <QtCore/QFile>

using namespace App;

Config *Config::getInstance() {
    return new Config();
}

void Config::loadStyles() {
    QString strCss;
    QStringList styles;
    styles << "../assets/styles/app.qss"
           << "../assets/styles/buttons.qss"
           << "../assets/styles/labels.qss";

    for (auto &filename : styles) {
        QFile file(filename);
        file.open(QFile::ReadOnly);
        strCss += QLatin1String(file.readAll());
    }

    qApp->setStyleSheet(strCss);
}


