#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";
qint32 max = 9500;

Runner::Runner(QObject *parent, qint32 begin) :
    QObject(parent)
{
    iid = begin;
    cnt = 0;
    sqlsaver = new SqlSaver("data.db");
    connect(this, SIGNAL(currentDone()), this, SLOT(getNext()));
}

void Runner::run()
{
    emit currentDone();
}

// used for displaying page contents on screen
void Runner::displayContent()
{
    qDebug() << retriever->content();
    emit finished();
}

void Runner::processContent()
{
    QString newContent = retriever->content();
    QString title;
    float price = 0;

    // free current retriever
    retriever->deleteLater();

    Interpreter::parse_item(newContent, &title, &price);
    if(price > 0) { // skip invalid or inexistent products
        sqlsaver->addPrice(iid, title, price);
        cnt++;
    }

    emit currentDone();
}

void Runner::getNext()
{
    while(sqlsaver->exists(++iid) && iid < max);

    //qDebug() << "Progress:" << (qint32)((float)iid / max*100) << "% ...";
    qDebug() << iid << "/" << max << "-" << (qint32)((float)iid / max*100) << "% - count:" << cnt;

    if(iid >= max) {
        sqlsaver->close();
        qDebug() << "Total items fetched:" << cnt;
        emit finished();
    }

    retriever = new Retriever(QString(baseurl+QString::number(iid)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}
