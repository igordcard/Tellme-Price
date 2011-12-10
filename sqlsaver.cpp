#include "sqlsaver.h"
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

SqlSaver::SqlSaver(QString filename)
{
    // load database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filename);
    if(!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError();
    }

    // ready query up
    query = new QSqlQuery(db);

    setStructure();
}

void SqlSaver::addPrice(qint32 id, QString title, float price)
{
    qint32 today;

    // get timestamp of today (at midnight), used as an unique db day identifier
    today = QDateTime::currentDateTime().toTime_t();
    today -= today % (86400);

    // insert item
    query->prepare("INSERT INTO items (itemId, title) VALUES (:itemId, :title)");
    query->bindValue(":itemId", QVariant(id));
    query->bindValue(":title", QVariant(title));
    if(!query->exec()) {
        qDebug() << "Failed inserting item:" << query->lastError().text();
    }

    // insert price of today
    query->prepare("INSERT INTO trends (itemId, day, price) VALUES (:itemId, :day, :price)");
    query->bindValue(":itemId", QVariant(id));
    query->bindValue(":day", QVariant(today));
    query->bindValue(":price", QVariant(price));
    if(!query->exec()) {
        qDebug() << "Failed inserting price:" << query->lastError().text();
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
        createTables();
    }
}

void SqlSaver::createTables()
{
    query->prepare("CREATE TABLE items ("
                   "itemId INTEGER PRIMARY KEY,"
                   "title VARCHAR(64))");
    if(!query->exec()) {
        qDebug() << "Failed creating database structure:" << query->lastError().text();
    }

    query->prepare("CREATE TABLE trends ("
                   "itemId INTEGER,"
                   "day INTEGER,"
                   "price REAL NOT NULL,"
                   "FOREIGN KEY (itemId) REFERENCES items(itemId)"
                   "PRIMARY KEY (itemId, day))");
    if(!query->exec()) {
        qDebug() << "Failed creating database structure:" << query->lastError().text();
    }
}

void SqlSaver::close()
{
    db.close();
}
