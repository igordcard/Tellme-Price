#ifndef SQLSAVER_H
#define SQLSAVER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QVariant>

class SqlSaver
{
public:
    SqlSaver(QString filename);
    void addPrice(qint32 id, QString title, float price);
    bool exists(qint32 id);
    void setStructure();
    void close();

private:
    QSqlDatabase db;
    QSqlQuery *query;
    void createTables();
    QVariant today();
};

#endif // SQLSAVER_H
