#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";
qint32 max = 9400;

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    iid = 9300;
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

    Interpreter::parse_item(newContent, &title, &price);
    if(price > 0) { // skip invalid or inexistent products
        qDebug() << "Writing item:" << iid;
        sqlsaver->addPrice(iid, title, price);
        cnt++;
    }
    iid++;

    emit currentDone();
}

void Runner::getNext()
{
    if(iid > max) {
        sqlsaver->close();
        qDebug() << "Total items fetched:" << cnt;
        emit finished();
    }

    retriever = new Retriever(QString(baseurl+QString::number(iid)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}
