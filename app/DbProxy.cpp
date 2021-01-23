#include "DbProxy.h"

using namespace App;

DbProxy::DbProxy() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("githelperdb");
    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("password");
    if (!db.open()) {

    }
}

QVector<Command> DbProxy::getMainCommands() {
    QSqlQuery query;
    QVector<Command> commands;

    query.exec("SELECT commands.id, commands.name, commands.usage, commands.note_en as note, count(*) > 1 AS has_child "
               "FROM commands "
               "JOIN commands_children cc on commands.id = cc.command_id "
               "WHERE is_main = 1 "
               "GROUP BY commands.name");

    auto record = query.record();
    while(query.next()) {
        commands.push_back({
            query.value(record.indexOf("id")).toUInt(),
            query.value(record.indexOf("name")).toString(),
            query.value(record.indexOf("usage")).toString(),
            query.value(record.indexOf("note")).toString(),
            query.value(record.indexOf("has_child")).toBool()
       });
    }

    return commands;
}

QVector<Command> DbProxy::getChilrenCommands(unsigned id) {
    return QVector<Command>{};
}

DbProxy::~DbProxy() {
    db.close();
}
