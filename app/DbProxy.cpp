#include "DbProxy.h"

using namespace App;

DbProxy::DbProxy() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("githelperdb");
    db.setUserName("root");
    db.setHostName("localhost");
    db.setPassword("password");
    db.open();
}

QVector<Command> DbProxy::getMainCommands() {
    QSqlQuery query;
    QVector<Command> commands;

    query.exec("SELECT * FROM commands WHERE is_main = 1");
    auto record = query.record();
    while(query.next()) {
        commands.push_back({
            query.value(record.indexOf("id")).toUInt(),
            query.value(record.indexOf("name")).toString(),
            query.value(record.indexOf("usage")).toString(),
            query.value(record.indexOf("note_en")).toString()
       });
    }

    return commands;
}

DbProxy::~DbProxy() {
    db.close();
}
