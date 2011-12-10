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
    QVariant p_itemId = QVariant(id);
    QVariant p_title = QVariant(title);
    QVariant p_price = QVariant(price);
    QVariant p_today;

    // get timestamp of today (at midnight), used as an unique db day identifier
    today = QDateTime::currentDateTime().toTime_t();
    today -= today % (86400);
    p_today = QVariant(today);

    // check if current item already exists
    query->prepare("SELECT itemId FROM items WHERE itemId=:itemId");
    query->bindValue(":itemId", p_itemId);
    if(!query->exec()) {
        qDebug() << "Couldn't check for items:" << query->lastError().text();
    }
    else if(!query->next()) {
        // insert item
        query->prepare("INSERT INTO items (itemId, title) VALUES (:itemId, :title)");
        query->bindValue(":itemId", p_itemId);
        query->bindValue(":title", p_title);
        if(!query->exec()) {
            qDebug() << "Failed inserting item:" << query->lastError().text();
        }
    }

    // check if current item has already been priced today
    query->prepare("SELECT itemId FROM trends WHERE itemId=:itemId AND day=:day");
    query->bindValue(":itemId", p_itemId);
    query->bindValue(":day", p_today);
    if(!query->exec()) {
        qDebug() << "Couldn't check for dates:" << query->lastError().text();
    }
    else if(!query->next()) {
        // insert price of today
        query->prepare("INSERT INTO trends (itemId, day, price) VALUES (:itemId, :day, :price)");
        query->bindValue(":itemId", p_itemId);
        query->bindValue(":day", p_today);
        query->bindValue(":price", p_price);
        if(!query->exec()) {
            qDebug() << "Failed inserting trend:" << query->lastError().text();
        }
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
