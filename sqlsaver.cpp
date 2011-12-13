#include "sqlsaver.h"
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include <QTextStream>

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

// TODO: separate check exists ?
void SqlSaver::addPrice(qint32 id, QString title, float price)
{
    QVariant p_itemId = QVariant(id);
    QVariant p_title = QVariant(title);
    QVariant p_price = QVariant(price);
    QVariant p_today = today();

    // check if current item already exists
//    query->prepare("SELECT itemId FROM items WHERE itemId=:itemId");
//    query->bindValue(":itemId", p_itemId);
//    if(!query->exec()) {
//        qDebug() << "Couldn't check for items:" << query->lastError().text();
//    }
//    else if(!query->next()) {
        // insert item
        //qDebug() << "Inserting new item:" << id << ":" << title;
        query->prepare("INSERT INTO items (itemId, title) VALUES (:itemId, :title)");
        query->bindValue(":itemId", p_itemId);
        query->bindValue(":title", p_title);
        query->exec();
//        if(!query->exec()) {
//            qDebug() << "Failed inserting item" << id << ":" << query->lastError().text();
//        }
//    }
//    else {
//        qDebug() << "Item" << id << "already in database";
//    }

    // check if current item has already been priced today
//    query->prepare("SELECT itemId FROM trends WHERE itemId=:itemId AND day=:day");
//    query->bindValue(":itemId", p_itemId);
//    query->bindValue(":day", p_today);
//    if(!query->exec()) {
//        qDebug() << "Couldn't check for dates:" << query->lastError().text();
//    }
//    else if(!query->next()) {
        // insert price of today
        //qDebug() << "Inserting new price:" << id << ":" << price;
        query->prepare("INSERT INTO trends (itemId, day, price) VALUES (:itemId, :day, :price)");
        query->bindValue(":itemId", p_itemId);
        query->bindValue(":day", p_today);
        query->bindValue(":price", p_price);
        query->exec();
//        if(!query->exec()) {
//            qDebug() << "Failed inserting trend:" << query->lastError().text();
//        }
//    }
//    else {
//        qDebug() << "Price of today already associated with item";
//    }
}

// checks if both item and its today price exist
bool SqlSaver::exists(qint32 id)
{
    QVariant p_itemId = QVariant(id);
    QVariant p_today = today();

    // check if current item already exists
    query->prepare("SELECT itemId FROM items WHERE itemId=:itemId");
    query->bindValue(":itemId", p_itemId);
    if(!query->exec()) {
        qDebug() << "Couldn't check for items:" << query->lastError().text();
        return true;
    }
    else if(!query->next()) {
        return false;
    }

    // check if current item has already been priced today
    query->prepare("SELECT itemId FROM trends WHERE itemId=:itemId AND day=:day");
    query->bindValue(":itemId", p_itemId);
    query->bindValue(":day", p_today);
    if(!query->exec()) {
        qDebug() << "Couldn't check for dates:" << query->lastError().text();
        return true;
    }
    else if(!query->next()) {
        return false;
    }

    return true;
}

// get timestamp of today (at midnight), used as an unique db day identifier
QVariant SqlSaver::today() {
    qint32 today;
    QVariant p_today;

    today = QDateTime::currentDateTime().toTime_t();
    today -= today % (86400);
    p_today = QVariant(today);

    return p_today;
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
