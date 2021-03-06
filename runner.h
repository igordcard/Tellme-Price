#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QRegExp>
#include "retriever.h"
#include "interpreter.h"
#include "sqlsaver.h"

class Runner : public QObject
{
    Q_OBJECT

public:
    explicit Runner(QObject *parent = 0, qint32 begin = 0, qint32 end = 0, QString path = "data.db", QString source = "file.source");

signals:
    void finished();
    void currentDone();

public slots:
    void run();

private slots:
    void displayContent();
    void processContent();
    void getNext();

private:
    Interpreter *interpreter;
    Retriever *retriever;
    SqlSaver *sqlsaver;
    //Saver *saver;
    qint32 max;
    qint32 iid;
    qint32 cnt;
    QTime duration;
    QString format_time(int time);
};

#endif // RUNNER_H
