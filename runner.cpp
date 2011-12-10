#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";
qint32 max = 9500;

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    iid = 0;
    sqlsaver = new SqlSaver("data.db");
    connect(this, SIGNAL(currentDone()), this, SLOT(getNext()));
    title_exp = new QRegExp("<a href=\"Produto.asp\\?Artigo\\=[0-9]+\" class=\"LetraLaranja\">([\\w\\-\\.\\,/\\&\\; _\(\\)\\+\'\"\\º\\±]+)</a>");
    price_exp = new QRegExp("<strong>[ \t\r\n]*&euro; ([0-9,]+)[ \t\r\n]*</strong>");
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
    QString title;
    float price;

    if(newContent.length() > 1024) {
        qDebug() << "Writing item:" << iid;
        title_exp->indexIn(newContent);
        price_exp->indexIn(newContent);
        title = title_exp->cap(1);
        price = price_exp->cap(1).replace(",",".").toFloat();
        if(price > 0) { // skip obviously invalid products
            sqlsaver->addPrice(iid, title, price);
        }
    }

    iid++;

    emit currentDone();
}

void Runner::getNext()
{
    if(iid > max) {
        sqlsaver->close();
        emit finished();
    }

    retriever = new Retriever(QString(baseurl+QString::number(iid)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}
