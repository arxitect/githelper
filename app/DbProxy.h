/****************************************************************************
 *
 * This file is part of the Git Helper application.
 *
 *  The class is designed to get
 *  data from the database
 *
****************************************************************************/
#ifndef GIT_HELPER_DBPROXY_H
#define GIT_HELPER_DBPROXY_H

#include <QtSql>

namespace App {

struct Command {
    unsigned id;
    QString name;
    QString usage;
    QString note;
    bool hasChild;
};

class DbProxy {
private:
    QSqlDatabase db;
public:
    DbProxy(DbProxy &) = delete;
    void operator=(const DbProxy &) = delete;
    explicit DbProxy();
    ~DbProxy();

    QVector<Command> getMainCommands();
    QVector<Command> getChilrenCommands(unsigned id);
};

}

#endif //GIT_HELPER_DBPROXY_H
