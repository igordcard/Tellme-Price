#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include "retriever.h"
#include "interpreter.h"
#include "saver.h"

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
    Saver *saver;
    qint32 c;
    void cleanup();
};

#endif // RUNNER_H
