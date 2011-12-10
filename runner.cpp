#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";
qint32 max = 9500;

Runner::Runner(QObject *parent) :
    QObject(parent)
{
    iid = 0;
    saver = new SqlSaver("data.db");
    //saver->createStructure();
    //saver = new Saver("data.csv");
    //saver->appendLine("ID,Title,Price,URL");
    connect(this, SIGNAL(currentDone()), this, SLOT(getNext()));
    title_exp = new QRegExp("<a href=\"Produto.asp\\?Artigo\=[0-9]+\" class=\"LetraLaranja\">([a-zA-Z0-9\-\./ ]+)</a>");
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
    QString price;
    QString formatted;

    if(newContent.length() > 1024) {
        qDebug() << "Writing item:" << iid;
        title_exp->indexIn(newContent);
        price_exp->indexIn(newContent);
        title = title_exp->cap(1);
        price = price_exp->cap(1);
        price.replace(",",".");
        formatted = QString::number(iid) + "," + title + "," + price + "," + baseurl+QString::number(iid); // use iid + "," to lol a lil bit (and learn)
        saver->addPrice(iid, title, price.toFloat());
        //saver->appendLine(formatted);
    }

    iid++;

    emit currentDone();
}

void Runner::getNext()
{
    if(iid > max)
        emit finished();

//    if(iid % 32 == 0) {
//        qDebug() << "Writing to disk...";
//        saver->flush();
//    }

    retriever = new Retriever(QString(baseurl+QString::number(iid)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}
