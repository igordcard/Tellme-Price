#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QDebug>
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

public slots:
    void run();

private slots:
    void displayContent();

private:
    Retriever *retriever;
    Interpreter *interpreter;
    Saver *saver;
};

#endif // RUNNER_H
