#include "sqlsaver.h"
#include <QDebug>
#include <QSqlError>

SqlSaver::SqlSaver(QString filename)
{
    // load database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if(!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError();
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
            qDebug() << "Loading existing database...";
            return;
        }

        qDebug() << "Creating new database...";
        createQ->prepare("CREATE TABLE prices (id INTEGER PRIMARY KEY, title VARCHAR(64), price REAL)");
        if(!createQ->exec()) {
            qDebug() << "Failed creating database structure:" << createQ->lastError().text();
        }
    }
}

void SqlSaver::close()
{
    db.close();
}
