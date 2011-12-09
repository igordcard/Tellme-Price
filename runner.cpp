#include <QDebug>
#include "retriever.h"
#include "runner.h"

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    retriever = new Retriever(QString("http://www.pcdiga.com/pcdiga/"));
}

void Runner::run()
{
    connect(retriever, SIGNAL(pageRetrieved()), this, SLOT(displayContent()));
}

void Runner::displayContent()
{
    qDebug() << retriever->content();
    emit finished();
}
