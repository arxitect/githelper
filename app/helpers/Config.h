/****************************************************************************
 *
 * This file is part of the Git Helper application.
 *
 * Application configuration.
 *
****************************************************************************/
#ifndef GIT_HELPER_CONFIG_H
#define GIT_HELPER_CONFIG_H

#include <QtSql>

namespace App {

class Config {
private:
    explicit Config() : rootPath(ROOT_PATH), appName("Git helper"){};
    static Config* config;
    QSqlDatabase db;
    const QString rootPath;
    const QString appName;
public:
    Config(Config &) = delete;
    void operator=(const Config &) = delete;
    ~Config();

    static Config* getInstance() ;
    void loadStyles(bool darkMode = false) const;
    void loadSQLConnection();
    [[nodiscard]] QString getRootPath() const;
    [[nodiscard]] QString getAppName() const;
};

}

#endif //GIT_HELPER_CONFIG_H
