#include "DbProxy.h"

using namespace App;

/* getElements: method getting elements from db by passing string */
QVector<Command> DbProxy::getElements(const QString& qString) {
    QSqlQuery query;
    QVector<Command> commands;

    query.exec(qString);
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

QVector<Command> DbProxy::getMainCommands(){

    QString qString = "SELECT commands.id, commands.name, commands.usage, commands.note_en as note,"
               " count(commands_children.id) > 0 has_child "
               "FROM commands "
               "LEFT OUTER JOIN commands_children on commands.id = commands_children.command_id "
               "WHERE is_main = 1 "
               "GROUP BY commands.id";

    return getElements(qString);
}

QVector<Command> DbProxy::getChildCommands(unsigned id) {

    QString qString = "SELECT commands.id, commands.name, commands.usage, commands.note, count(commands_children.id) > 0 has_child "
                  "FROM (SELECT commands.id, commands.name, commands.usage, commands.note_en as note "
                  "FROM commands_children "
                  "JOIN commands ON commands.id = commands_children.child_id "
                  "WHERE commands_children.command_id = %1) as commands "
                  "LEFT OUTER JOIN commands_children on commands.id = commands_children.command_id "
                  "GROUP BY commands.id";

    return getElements(qString.arg(id));
}

