#ifndef SQLSAVER_H
#define SQLSAVER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>

class SqlSaver
{
public:
    SqlSaver(QString filename);
    void SqlSaver::addPrice(QString str);

private:
    QSqlDatabase db;
    QSqlQuery insert;
};

#endif // SQLSAVER_H
