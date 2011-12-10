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
    void setStructure();
    void close();

private:
    QSqlDatabase db;
    QSqlQuery *createQ;
    QSqlQuery *insertQ;
    QSqlQuery *selectQ;
};

#endif // SQLSAVER_H
