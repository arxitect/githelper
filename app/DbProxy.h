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
    QString note_en;
    QVector<Command> children;
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
};

}

#endif //GIT_HELPER_DBPROXY_H
