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
    static QVector<Command> getElements(const QString& qString);
public:
    static QVector<Command> getMainCommands();
    static QVector<Command> getChildCommands(unsigned id);
};

}

#endif //GIT_HELPER_DBPROXY_H
