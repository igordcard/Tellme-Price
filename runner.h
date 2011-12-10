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
    explicit Runner(QObject *parent = 0);

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
    Retriever *retriever;
    Interpreter *interpreter;
    SqlSaver *sqlsaver;
    //Saver *saver;
    qint32 iid;
    QRegExp *title_exp;
    QRegExp *price_exp;
};

#endif // RUNNER_H
