#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    c = 0;
    connect(this, SIGNAL(currentDone()), this, SLOT(getNext()));
}

void Runner::run()
{
    emit currentDone();
}

void Runner::displayContent()
{
    qDebug() << retriever->content();
    emit finished();
}

void Runner::processContent()
{
    QString newContent = retriever->content();

    if(newContent.length() > 1024) {
        saver = new Saver("prices/item-"+QString::number(c)+".html");
        qDebug() << "Writing item " << c;
        saver->appendLine(newContent);
    }

    c++;

    emit currentDone();
}

void Runner::getNext()
{
    if(c > 100)
        emit finished();

    //cleanup();
    retriever = new Retriever(QString(baseurl+QString::number(c)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}

void Runner::cleanup()
{
    if(c > 0) {
        delete retriever;
        delete saver;
    }
}
