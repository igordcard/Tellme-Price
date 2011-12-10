#include "sqlsaver.h"
#include <QDebug>
#include <QSqlError>

SqlSaver::SqlSaver(QString filename)
{
    // load database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    qDebug() << "Opening DB...";
    if(!db.open()) {
        qFatal("Failed to open database.");
    }

    // define queries
    createQ = new QSqlQuery(db);
    insertQ = new QSqlQuery(db);
    selectQ = new QSqlQuery(db);

    setStructure();
}

void SqlSaver::addPrice(qint32 id, QString title, float price)
{
    insertQ->prepare("INSERT INTO prices (id, title, price) VALUES (:id, :title, :price)");
    insertQ->bindValue(":id", QVariant(id), QSql::In);
    insertQ->bindValue(":title", QVariant(title), QSql::In);
    insertQ->bindValue(":price", QVariant(price), QSql::In);

    if(!insertQ->exec()) {
        qDebug() << "Failed inserting record:" << insertQ->lastError().text();
    }
}

void SqlSaver::setStructure()
{
    if(db.isOpen()) {

        if(db.tables().count() > 0) {
            qDebug() << "There are already tables, nothing to do.";
            return;
        }

        qDebug() << "Creating a new DB...";
        createQ->prepare("CREATE TABLE prices (id INTEGER PRIMARY KEY, title VARCHAR(64), price REAL)");
        if(!createQ->exec()) {
            qDebug() << "Failed creating database structure:" << createQ->lastError().text();
        }
    }
}
