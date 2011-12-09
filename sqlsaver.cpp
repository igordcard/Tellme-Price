#include "sqlsaver.h"

SqlSaver::SqlSaver(QString filename)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if(!db.open()) {
        qFatal("Failed to connect to database.");
    }
    insert = new QSqlQuery(db);
    insert.prepare("INSERT INTO prices (id, title, price) VALUES (:id, :title, :price)");
}

SqlSaver::addPrice(qint32 id, QString title, qreal price)
{
    insert.bindValue(":id", id);
    insert.bindValue(":title", title);
    insert.bindValue(":price", price);
}
